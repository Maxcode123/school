def main():

    valid_text = produce_valid_text()

    text_list = valid_text.split(sep=" ")

    words = count_occurrence(text_list)
    two_chars = count_occurrence(text_list, chars_length=2)
    three_chars = count_occurrence(text_list, chars_length=3)

    last_10 = famous_last_words(words)

    print(f"Famous last words: {last_10}")
    print(f"Three most common initial two characters: {two_chars[-3:]}")
    print(f"Three most common initial three characters {three_chars[-3:]}")


def produce_valid_text():
    "Returns the text in a string containing only lowercase letters and space."

    file_path = "./two_cities_ascii.txt"

    with open(file_path) as text_file:
        text = text_file.read()

    valid_chars = [
        "a",
        "b",
        "c",
        "d",
        "e",
        "f",
        "g",
        "h",
        "i",
        "j",
        "k",
        "l",
        "m",
        "n",
        "o",
        "p",
        "q",
        "r",
        "s",
        "t",
        "u",
        "v",
        "w",
        "x",
        "y",
        "z",
        " ",
    ]
    text = text.lower()
    valid_text = ""

    for char in text:
        if char in valid_chars:
            valid_text += char
    return valid_text


def count_occurrence(text_list, chars_length=None):
    """Returns a sorted listed of tuples with keys and occurences of keys in
    the text_list. Keys can be whole words or a number of characters."""
    if chars_length is None:
        end = lambda word: len(word)
    else:
        end = lambda word: chars_length
    occurence = {}
    for word in text_list:
        if len(word) < end(word):
            continue
        occurence[word[: end(word)]] = occurence.get(word[: end(word)], 0) + 1
    occurence = sorted(occurence.items(), key=lambda x: x[1])

    return occurence


def famous_last_words(words):
    """Returns the 10 most famous words, if some words appear the same number
    times, it drops the first of them. The words list must be sorted."""
    last_10 = words[-10:]
    for index, _ in enumerate(last_10[:-1]):
        if last_10[index][1] == last_10[index + 1][1]:
            shift_and_remove(words, last_10, index)
    return last_10


def shift_and_remove(words, last_10, index):
    """Removes the item with index from last_10 and shifts all items from the
    start up to index one place to the right."""
    for idx, _ in enumerate(last_10[: index + 1]):
        last_10[index - idx] = words[-len(last_10[index:]) - 1 - idx]


if __name__ == "__main__":
    main()
