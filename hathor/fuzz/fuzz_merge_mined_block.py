#!/usr/bin/python3

import atheris

with atheris.instrument_imports():
    import sys
    from struct import error as StructError
    from hathor.transaction.exceptions import InvalidOutputValue
    from hathor.transaction import MergeMinedBlock

def TestOneInput(data):
    if len(data) < 8:
        return

    try:
        MergeMinedBlock.create_from_struct(data)
    except (ValueError, InvalidOutputValue, StructError, AssertionError):
        pass

def main():
    atheris.Setup(sys.argv, TestOneInput, enable_python_coverage=True)
    atheris.Fuzz()

if __name__ == "__main__":
    main()
