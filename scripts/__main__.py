import sys
import textwrap

def main():
    for arg in sys.argv[1:]:
        # im bored, hackish method
        code = f"""
        from commands.{arg} import {arg}
        {arg}()
        """

        exec(textwrap.dedent(code))

if __name__ == "__main__":
    main()
