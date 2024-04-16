/*! \brief send raw file to a named printer tool
 *         This Programm sends a Text file to a named printer 
 *
 *  The program prints the raw data from a file to a printer.  
 */

#include <windows.h>
#include <stdio.h>

void PrintRawDataToPrinter(const char* printerName, const char* fileName, const char* jobName) {
    HANDLE hPrinter;
    DOC_INFO_1 docInfo;
    DWORD bytesWritten;
    BYTE buffer[1024];
    FILE *file;

    // Step 1: Open the printer
    if (!OpenPrinter((LPSTR)printerName, &hPrinter, NULL)) {
        fprintf(stderr, "Failed to open the printer %s\n", printerName);
        return;
    }

    // Step 2: Set up the document info
    docInfo.pDocName = (LPTSTR)jobName;
    docInfo.pOutputFile = NULL;
    docInfo.pDatatype = "RAW";

    // Step 3: Start a document
    if (StartDocPrinter(hPrinter, 1, (LPBYTE)&docInfo) == 0) {
        fprintf(stderr, "Failed to start the document on the printer\n");
        ClosePrinter(hPrinter);
        return;
    }

    // Step 4: Start a page
    if (!StartPagePrinter(hPrinter)) {
        fprintf(stderr, "Failed to start a page\n");
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);
        return;
    }

    // Step 5: Read from the text file and send to printer
    if ((file = fopen(fileName, "rb")) == NULL) {
        fprintf(stderr, "Failed to read the file %s\n", fileName);
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);
        return;
    }

    while (!feof(file)) {
        size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
        if (!WritePrinter(hPrinter, buffer, bytesRead, &bytesWritten)) {
            fprintf(stderr, "Failed to write to printer\n");
            break;
        }
    }

    fclose(file);

    // Step 6: End the page and document
    EndPagePrinter(hPrinter);
    EndDocPrinter(hPrinter);

    // Step 7: Close the printer
    ClosePrinter(hPrinter);
}

/**
 * Check if a file exists and is readable.
 *
 * @param fileName The path to the file to check.
 * @return 1 if the file exists and is readable, 0 otherwise.
 */
int isFileReadable(const char *fileName) {
    FILE *file = fopen(fileName, "r"); // Try to open the file in read mode
    if (file != NULL) {
        fclose(file); // Close the file if it was successfully opened
        return 1; // File exists and is readable
    }
    return 0; // File does not exist or is not readable
}

int main(int argc, char* argv[]) {
    char* printerName = NULL;
    char* fileName = NULL;
    char* jobName = "RawPrintJob";

    // parse command line arguments 
    for (int i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], "--printer") == 0) {
            printerName = argv[++i];
        } 
        if (strcmp(argv[i], "--file") == 0) {
            fileName = argv[++i];
        }
        if (strcmp(argv[i], "--jobname") == 0) {
            jobName = argv[++i];
        }
    }

    // check if all needed parameter are set
    if (printerName == NULL || fileName == NULL) {
        fprintf(stderr, "Usage: %s --printer <printer_name> --file <file_name> --jobname <string>\n", argv[0]);
        return 1;
    }

    // check if file is readable (before printing)
    if(!isFileReadable(fileName)) {
        fprintf(stderr, "Failed to read file from %s\n", fileName);
        return 1;
    }

    // Print now
    PrintRawDataToPrinter(printerName, fileName, jobName);

    return 0;
}
