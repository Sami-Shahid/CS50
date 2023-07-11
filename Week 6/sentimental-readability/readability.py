# TODO
words = input("Text: ")
swords = words.split()
sen = words.count(".")
sen += words.count("!")
sen += words.count("?")

s = (sen/len(swords)) * 100
l = 0
for i in swords:
    if "." in i or "!" in i or "?" in i:
        l-=1
    l+= len(i)
l /= len(swords)
l*=100
grade = 0.0588 * l - 0.296 * s - 15.7
if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print("Grade",int(grade))