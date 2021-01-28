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
    desired input PNG.  Please input a PNG only.')

def message_encoder():
    """Takes the source text file and converts to 8-bit binary.
    """
    pass

def read_source():
    pass

def write_target():
    pass

# format(ord('c'), '08b')

if __name__ == "__main__":
    pass