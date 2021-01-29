"""PNG Opacity Message -- Sizing Calculator
"""

def message_bit_counter(TextFile):
    """Reads text file, convert to ASCII, find bits, and count.

    Arguments:
        d

    Returns:
        d
    """
    text = []
    reader = None

    try:
        # Always ensure there are no issues with opening file.
        # TODO: Check if file exists beforehand.
        reader = open(file=TextFile, mode='r', encoding='UTF-8')
    except Exception:
        print(f'Error when attempting to read text file.')
        exit()

    characterCount = 0

    # Read all lines.
    lines = reader.readlines()
    for line in lines:
        for character in line:
            count += 1

    return count * 8

def calculator():
    pass

if __name__ == "__main__":
    pass