print("{", end="")
for i in range(0, 20):
    print(pow(129, i), end="")
    if i < 19:
        print(", ", end="")

print("}")