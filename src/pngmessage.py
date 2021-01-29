"""PNG Opacity Message Embedder
"""

import argparse
import png

_parser = argparse.ArgumentParser(description='PNG Opacity Message Embedder', epilog='\
    Further information can be found on the GitHub repository.', add_help=True)
_parser.add_argument('-t', '--input', type=str, help='Input text file to \
    embedd a message into the target image.', required=True)
_parser.add_argument('-o', '--output', type=str, help='Location and filename for \
    desired output file.', required=True)
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
        reader = open(file=TextFile, mode='r', encoding='UTF-8')
    except Exception:
        print(f'Error when attempting to read text file.')
        exit()

    overload = False

    # Read all lines.
    lines = reader.readlines()
    for line in lines:
        for character in line:
            # Convert to binary string.
            binData = format(ord(character), '08b')
            if len(binData) > 8:
                if character == '“' or character == '”':
                    binData = format(ord('"'), '08b')
                elif character == '’' or character == '‘':
                    binData = format(ord("'"), '08b')
                elif character == '—':
                    binData = format(ord("-"), '08b')
                elif character == "﻿":
                    binData = format(ord(" "), '08b')
                else:
                    binData = format(ord("?"), '08b')

            # Each bit is stored rather than storing a string of bits.
            # Even then, store as boolean.
            for bit in binData:
                if bit == '0':
                    text.append(False)
                else:
                    text.append(True)

            # Make sure we stay within boundries.
            # if len(text) / 8 >= AllowedCharacters:
            #     # Avoid going beyond the image size.
            #     print("Not all information was stored in the image.")
            #     overload = True
            #     break

        if overload:
            break

    # TODO: Print confirmation message for empty buffer
    # of more than 25% of available image real estate.
    print(AllowedCharacters)
    print(len(text) / 8)
    exit()
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
    bitsPerWidth = PNGData[0]
    counter = 0
    binIndex = 0

    for line in pngRGBA:
        index = 3
        counter = 0
        while counter < bitsPerWidth and binIndex < len(BinaryData):
            # Alter alpha channel
            if BinaryData[binIndex]:
                line[index] = 255
            else:
                line[index] = 128
            
            index += 4
            binIndex += 1
            counter += 1

        if binIndex >= len(BinaryData):
            break

    # TODO: Confirm we can write the the output location.
    png.from_array(pngRGBA, mode='RGBA').save(TargetFile)

    return None

if __name__ == "__main__":
    print("Warning, your image's opacity values _will_ be altered.")
    args = _parser.parse_args()
    pngData, dataLength = read_source(args.source)
    binaryData = message_encoder(args.input, dataLength)
    encodedPNG = write_target(args.output, binaryData, pngData)
