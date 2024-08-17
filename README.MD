# rawprn - RAW Print Tool

`rawprn` is a simple command-line tool for Windows that facilitates the direct transmission of files to a printer without the use of printer drivers. It is particularly useful for sending files in specific printer languages, such as ZPL or EPL, directly to connected printers.

## Installation

The tool requires no installation. It is a standalone executable file that can be executed directly under windows command line

## System Requirements

- 32 or 64-bit Windows operating system

## Usage

`rawprn` is executed via the command line with the following parameters:

```bash
rawprn --printer PRINTERNAME --file FILE [--jobname JOBNAME]
```

### Parameters

- `--printer`: The name of the target printer. (Required)
- `--file`: The path to the file to be printed. (Required)
- `--jobname`: The name of the print job. (Optional)

### Example

To send a ZPL file to a printer:

```bash
rawprn --printer "Zebra_ETL" --file "label.zpl" --jobname "LabelPrint"
```

### Valid Printer Names

To find valid printer names on your system, you can use PowerShell. Run the following command to list all available printers:

```powershell
Get-Printer | Format-List Name
```

This command will output a list of printer names installed on your system, which you can use with the `--printer` parameter in `rawprn`.

### Example Output

```plaintext
Name : Zebra_ETL
Name : HP_LaserJet
Name : Microsoft Print to PDF
```

You can then use any of these names as the value for the `--printer` parameter, if the name contains spaces, use double quotes on the parameter.

## Supported File Formats

`rawprn` supports the transmission of any file format. The requirement is that the target printer must be able to process the file format natively. Common formats include:

- **ZPL** (Zebra Programming Language)
- **EPL** (Eltron Programming Language)
- **PDF** (for printers that can directly process PDF files)

## Error Handling

Errors are displayed directly in the command line. Common error messages include:

- **Printer not found**: The specified printer name is incorrect or the printer is not connected.
- **File not found**: The specified file path is invalid or the file does not exist.

## License

This project is licensed under the MIT License. For more details, see the `LICENSE` file.

## Contact

For feedback or support inquiries, please contact [rawprn@contuino.de](mailto:rawprn@contuino.de).
