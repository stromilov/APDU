text = input()
mas = ['0x' + text[i:i+2] for i in range(0, len(text), 2)]
print("mas length = ", len(mas))
print("mas = ", *mas)
