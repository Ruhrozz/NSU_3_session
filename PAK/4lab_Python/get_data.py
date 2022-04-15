def get_data():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('a', type=str, help="First input file")
    parser.add_argument('b', type=str, help="Second input file")
    parser.add_argument('c', type=float, help="Probability")
    args = parser.parse_args()
    return args.a, args.b, args.c
