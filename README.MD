# rawprn a tool to send a raw textfile to a printer

This tool is used to send a raw textfile to a windwows printer, to mostly ignore the changes printer driver can do to manipulate the printed data. 

A common usecase is to create a textfile in a defined language (e.g. ZPL or EPL) and send these files raw to the defined printer.

## usage
...
rawprn.exe --printer <windows printer name> --file <file name> --jobname <Spooljob Name>
...
