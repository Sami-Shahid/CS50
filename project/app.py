import os

from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session

app = Flask(__name__)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)
nums = range(3)
lst = [[" ", " ", " "],[" ", " ", " "],[" ", " ", " "]]
turn = "X"
@app.route("/", methods=["GET", "POST"])
def start():
    global lst
    lst = [[" ", " ", " "],[" ", " ", " "],[" ", " ", " "]]

    return render_template("game.html", lst = lst, nums = nums, turn = turn)



@app.route("/game", methods=["GET", "POST"])
def game():
    global turn
    loc = request.form.get("x")
    lst[int(loc[0])][int(loc[1])] = turn

    if check(turn):
        print(check(turn))
        return render_template("winner.html", lst = lst, nums = nums, turn = turn)

    if turn == "X":
        turn = "O"
    else:
        turn = "X"
    return render_template("game.html", lst = lst, nums = nums, turn = turn)

def check(turn):
    for i in nums:
        won1 = True
        won2 = True
        for x in nums:
            won1 = won1 and (lst[i][x] == turn)
            won2 = won2 and (lst[x][i] == turn)
        if (won1 or won2):
            return True
    won1 = True
    won2 = True
    for i in nums:
        won1 = won1 and (lst[i][i] == turn)
        won2 = won2 and (lst[i][2-i] == turn)
    if won1 or won2:

        return True

    return False

