import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portfolio = {}
    sum = 0
    x = db.execute("SELECT * FROM History WHERE user_id = ?", session["user_id"])
    for i in x:
        symbol = i["symbol"]
        if symbol not in portfolio.keys():
            portfolio[symbol] = [i["shares"], lookup(symbol)["price"]]
        elif i["type"] == "buy":
            portfolio[symbol][0] += i["shares"]
        else:
            portfolio[symbol][0] -= i["shares"]
    a = list(portfolio.keys())
    for i in a:
        if portfolio[i][0] == 0:
            portfolio.pop(i)
        else:
            sum+=portfolio[i][0] * portfolio[i][1]



    return render_template("index.html", portfolio = portfolio, sum = sum, cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        if not symbol:
            return apology("must provide symbol", 400)
        if not shares:
            return apology("must provide shares", 400)
        if not shares.isdigit():
            return apology("shares must be a number", 400)
        stock = lookup(symbol)
        if not stock:
            return apology("Invalid symbol", 400)
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        price = stock["price"] * int(shares)
        if price > cash:
            return apology("Not enough cash", 400)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - price, session["user_id"])
        db.execute("INSERT INTO History (user_id, symbol, shares, price, type, date) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], symbol.upper(), shares, stock["price"], "buy",  datetime.now())
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    hist = db.execute("SELECT * FROM History WHERE user_id = ?", session["user_id"])
    print(hist)
    return render_template("history.html", hist = hist)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        '''
        if not symbol:
            return apology("must provide symbol", 400)
        if not stock:
            return apology("Invalid symbol", 400)
        return render_template("quoted.html", stock = stock)'''
        stock = lookup(request.form.get("symbol"))
        if stock == None:
            return apology("invalid stock symbol", 400)
        stock["price"] = f'{stock["price"]:.2f}'
        # Return template with stock quote, passing in symbol dict
        return render_template("quoted.html", stock = stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    user = request.form.get("username")
    passcode = request.form.get("password")
    con = request.form.get("confirmation")
    rows = db.execute("SELECT * FROM users WHERE username = ?", user)

    if request.method == "POST":
        print(db.execute("SELECT username FROM users"))
        if not user:
            return apology("must provide username", 400)
        elif not passcode:
            return apology("must provide password", 400)
        elif not con:
            return apology("must provide conformation", 400)
        elif con != passcode:
            return apology("password is not the same as conformation", 400)
        elif len(rows) != 0:
            return apology("username is already taken", 400)
        else:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", user, generate_password_hash(passcode),)
            return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    portfolio = {}
    x = db.execute("SELECT * FROM History WHERE user_id = ?", session["user_id"])
    for i in x:
        symbol = i["symbol"]
        if symbol not in portfolio.keys():
            portfolio[symbol] = [i["shares"], lookup(symbol)["price"]]
        elif i["type"] == "buy":
            portfolio[symbol][0] += i["shares"]
        else:
            portfolio[symbol][0] -= i["shares"]
    a = list(portfolio.keys())
    for i in a:
        if portfolio[i][0] == 0:
            portfolio.pop(i)
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("must provide symbol", 403)
        shares = int(request.form.get("shares"))

        if not shares:
            return apology("must provide shares", 403)
        if int(shares) > int(portfolio[symbol][0]):
            return apology("don't have that much shares", 400)
        cash =  db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        money = shares * portfolio[symbol][1]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + money, session["user_id"])
        db.execute("INSERT INTO History (user_id, symbol, shares, price, type, date) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], symbol.upper(), shares, portfolio[symbol][1], "sell",  datetime.now())
        return redirect("/")

    else:
        return render_template("sell.html", stock = portfolio.keys())
