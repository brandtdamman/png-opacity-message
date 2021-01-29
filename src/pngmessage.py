"""PNG Opacity Message Embedder
"""

import argparse
import png

_parser = argparse.ArgumentParser(description='PNG Opacity Message Embedder', epilog='\
    Further information can be found on the GitHub repository.', add_help=True)
_parser.add_argument('-t', '--input', type=str, help='Input text file to \
    embedd a message into the target image.')
_parser.add_argument('-o', '--output', type=str, help='Location and filename for \
    desired output file.')
_parser.add_argument('-i', '--source', type=str, help='Location and filename for \
    desired input PNG.  Please input a PNG only.', required=True)

def message_encoder(TextFile, AllowedCharacters):
    """Takes the source text file and converts to 8-bit binary.
    New line characters are omitted from translation.

    Arguments:
        TextFile        --      source text file
    
    Returns:
        text            --      binary formatted characters 
    """
    text = []
    reader = None

    try:
        # Always ensure there are no issues with opening file.
        # TODO: Check if file exists beforehand.
        reader = open(file=TextFile, mode='r')
    except Exception:
        print(f'Error when attempting to read text file.')
        exit()

    # Read all lines.
    lines = reader.readlines()
    for line in lines:
        for character in line:
            # Append binary information.
            text.append(format(ord(character), '08b'))
            if len(text) == AllowedCharacters:
                # Avoid going beyond the image size.
                break

    # TODO: Print confirmation message for empty buffer
    # of more than 25% of available image real estate.

    return text

def read_source(SourceFile):
    """Reads PNG file source and performs quick conversion.

    Arguments:
        SourceFile      --      source of PNG file

    Returns:
        pngData         --      RGBA information of file
        dataLength      --      allocated information limit
    """
    reader = png.Reader(filename=SourceFile)
    pngData = reader.asRGBA8()
    if pngData[0] % 8 != 0:
        # Seems arbitrary but necessary.
        print("Image is not divisible by 8.")
        exit()

    return (pngData, pngData[0] / 8 * pngData[1])

def write_target(TargetFile, BinaryData, PNGData):
    """Performs message encoding on PNG data whilst creating
    a new file.  Does a single-pass with opacity confirmation.

    Arguments:
        BinaryData      --      ascii binary information to encode
        PNGData         --      original PNG file to encode message onto

    Returns:
        encodedPNG      --      encoded PNG file to write
    """
    # Data format: make list from index 2 generator, every index 3 is alpha
    pngRGBA = list(PNGData[2])
    charactersPerWidth = PNGData[0] / 8
    counter = 0

    for line in pngRGBA:
        index = 3
        while counter < charactersPerWidth:
            # Alter alpha channel
            # TODO: FIX IT.  FIX THE TEXT LIST.  NO STRINGS PLS
            # line[index] =
    
    return (None)

if __name__ == "__main__":
    print("Warning, your image's opacity values _will_ be altered.")
    args = _parser.parse_args()
    pngData, dataLength = read_source(args.source)
    binaryData = message_encoder(args.input, dataLength)
