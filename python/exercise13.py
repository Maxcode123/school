from urllib.request import Request, urlopen
import ast


def main():
    req = Request(
        "https://drand.cloudflare.com/public/latest",
        headers={
            "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:31.0) Gecko/20130401 Firefox/31.0"
        },
    )
    byte_response = urlopen(req).read()

    response = convert_bytes_to_dict(byte_response)
    randomness = response["randomness"]

    hex_pair_list = [
        randomness[i : i + 2] for i in range(0, len(randomness), 2)
    ]
    dec_pair_list = [int(hex, 16) for hex in hex_pair_list]

    dec_pair_list = [dec % 80 for dec in dec_pair_list]
    dec_pair_set = set(dec_pair_list)

    byte_response = urlopen(
        "https://api.opap.gr/draws/v3.0/1100/last-result-and-active"
    ).read()
    response = convert_bytes_to_dict(byte_response)

    winning_numbers = response["last"]["winningNumbers"]["list"]

    random_winners = 0
    for number in dec_pair_set:
        if number in winning_numbers:
            random_winners += 1

    print(f"{random_winners} random numbers won in KINO.")


def convert_bytes_to_dict(bytes):
    "Returns a decoded dictionary of byte input."
    string = bytes.decode("UTF-8")
    dictionary = ast.literal_eval(string)
    return dictionary


if __name__ == "__main__":
    main()
