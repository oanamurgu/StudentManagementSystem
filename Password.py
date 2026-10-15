
import random
import string

caractere = string.ascii_letters + string.digits

parola = ""

for i in range(12):
    parola = parola + random.choice(caractere)

print("Parola generata este:", parola)

