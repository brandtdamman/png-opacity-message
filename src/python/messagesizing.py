"""PNG Opacity Message -- Sizing Calculator
"""

import argparse

_parser = argparse.ArgumentParser(description='PNG Opacity Message Embedder', epilog='\
    Further information can be found on the GitHub repository.', add_help=True)
_parser.add_argument('-i', '--input', type=str, help='Input text file to \
    embedd a message into the target image.', required=True)
_group = _parser.add_mutually_exclusive_group()
_group.add_argument('-w', '--width', type=int, help='Desired width for the \
    image.')
_group.add_argument('-l', '--height', type=int, help='Desired height for the \
    image.')

def message_bit_counter(TextFile):
    """Reads text file, convert to ASCII, find bits, and count.

    Arguments:
        TextFile            --      source text file

    Returns:
        characterCount      --      max characters allowed
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
    reader.close()  # close loose ends.
    for line in lines:
        for character in line:
            characterCount += 1
        # TODO: Count newline?

    return characterCount * 8

def size_calculator(CharacterCount, Width=None, Height=None):
    """Calculates the necessary size of the encodable image.

    Only one keyword argument is allowed.  If both are found to
    be provided, an error will be thrown.

    Arguments:
        CharacterCount  --      number of characters required

    Keyword Arguments:
        Width           --      (optional) desired width of image
        Height          --      (optional) desired height of image

    Returns:
        size            --      tuple of (width, height)
    """
    if Width and Height:
        print("Both keyword arguments were provided.  Exiting..")
        exit()

    # TODO: Find Pythonic implementation.
    possibleHeight = Height if Height else 0
    possibleWidth = Width if Width else 0
    
    if Width:
        # Find height.
        # Width calculation known.
        currWidth = Width
        while CharacterCount % currWidth != 0:
            currWidth -= 8

        possibleHeight = int(CharacterCount / currWidth)
        possibleWidth = currWidth
    else:
        currWidth = 8
        currHeight = possibleHeight
        while currWidth * currHeight != CharacterCount:
            while currWidth * currHeight < CharacterCount:
                currWidth += 8
            currHeight -= 1

        possibleWidth = int(CharacterCount / currHeight)
        possibleHeight = currHeight
    
    return (possibleWidth, possibleHeight)

if __name__ == "__main__":
    args = _parser.parse_args()
    characterCount = message_bit_counter(args.input)
    width, height = size_calculator(characterCount, Width=args.width, Height=args.height)
    print(f"{width}x{height} WxH for desired text.")