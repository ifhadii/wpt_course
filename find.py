def filter_lines(file_path, exclude_str):
    try:
        with open(file_path, 'r') as file:
            lines_read = 0
            lines_printed = 0
            for line in file:
                lines_read += 1
                if exclude_str not in line:
                    print(line.strip())
                    lines_printed += 1
            print(f"Total lines read: {lines_read}")
            print(f"Total lines printed: {lines_printed}")
    except FileNotFoundError:
        print(f"The file {file_path} does not exist.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
log_file_path = 'lfi_fuzzing.log'
exclude_string = 'did not result in'

filter_lines(log_file_path, exclude_string)
