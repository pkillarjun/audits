#!/usr/bin/python3

import atheris

with atheris.instrument_imports():
    import sys
    from hathor.transaction.scripts import parse_address_script

def TestOneInput(data):
    try:
        parse_address_script(data)
    except ValueError:
        pass

def main():
    atheris.Setup(sys.argv, TestOneInput, enable_python_coverage=True)
    atheris.Fuzz()

if __name__ == "__main__":
    main()
