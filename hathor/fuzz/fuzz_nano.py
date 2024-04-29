#!/usr/bin/python3

import atheris

with atheris.instrument_imports():
    import sys
    from struct import error as StructError
    from hathor.transaction.scripts import NanoContractMatchValues

def TestOneInput(data):
    try:
        NanoContractMatchValues.parse_script(data)
    except (StructError, IndexError):
        pass

def main():
    atheris.Setup(sys.argv, TestOneInput, enable_python_coverage=True)
    atheris.Fuzz()

if __name__ == "__main__":
    main()
