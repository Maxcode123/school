def main():

    file_path = "./two_cities_ascii.txt"

    with open(file_path) as text_file:
        text = text_file.read()

    bit_sequence = create_bit_sequence(text)
    bits16 = [
        bit_sequence[i : i + 16] for i in range(0, len(bit_sequence), 16)
    ]
    bits16.pop()  # remove last item to be sure that all elements are 16 bits

    even = find_divisible(bits16, 2)
    divisible_by_3 = find_divisible(bits16, 3)
    divisible_by_5 = find_divisible(bits16, 5)
    divisible_by_7 = find_divisible(bits16, 7)
    print(f"Percentage of even numbers = {even}%")
    print(f"Percentage of numbers divisible by 3 = {divisible_by_3}%")
    print(f"Percentage of numbers divisible by 5 = {divisible_by_5}%")
    print(f"Percentage of numbers divisible by 7 = {divisible_by_7}%")


def create_bit_sequence(text):
    """Returns the text received as a sequence of bits in a string. Each
    character is converted to a 7 bit binary number, then the first two and
    last two bits are kept and the rest are removed."""
    bits = ""
    for char in text:
        number = ord(char)
        binary = bin(number)[2:]
        binary = (7 - len(binary)) * "0" + binary
        outermost_bits = binary[:2] + binary[-2:]
        bits += outermost_bits
    return bits


def find_divisible(bit_list, number):
    """Returns the percentage of numbers in the bit_list that are divisible by
    the given number."""
    divisible = 0
    for bits in bit_list:
        if int(bits, 2) % number == 0:
            divisible += 1
    percentage = divisible / len(bit_list) * 100
    percentage = round(percentage, 2)
    return percentage


if __name__ == "__main__":
    main()
