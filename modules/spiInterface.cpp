#include "../main.h"
using namespace std;

class SpiInterface {
    public:
    SpiInterface(uint tx = 3, uint sck = 2, uint csn = 1, uint rx = 0, uint baudrate = 125000, uint CPOL = 0, uint CPHA = 0) {
        try {
            spi_init(spi0, baudrate);
            spi_set_slave(spi0, true);
            spi_set_format(spi0, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_LSB_FIRST);
            gpio_set_function(rx, GPIO_FUNC_SPI);
            gpio_set_function(sck, GPIO_FUNC_SPI);
            gpio_set_function(tx, GPIO_FUNC_SPI);
            gpio_set_function(csn, GPIO_FUNC_SPI);
            // Make the SPI pins available to picotool
            bi_decl(bi_4pins_with_func(rx, tx, sck, csn, GPIO_FUNC_SPI));
        } catch (...) {
            printf("Failure to initialize spi bus");
        }
    }
    void transferBytes(string* message) {
        try {
            char lengthDst[5];
            char lengthSrc[5];
            memset(lengthDst, 0x00, 5);
            memset(lengthSrc, 0x00, 5);
            string messageLength = to_string(message->size());
            for (int c = 0; c < messageLength.size(); c++) {
                lengthSrc[c] = messageLength.at(c);
            }
            spi_write_read_blocking(spi0, (uint8_t*)lengthSrc, (uint8_t*)lengthDst, 5);
            int receivedLength = stoi(string(lengthDst));
            printf(lengthDst);
            int transferLength = message->size() > receivedLength ? message->size() : receivedLength;
            char writeSet[transferLength];
            char readSet[transferLength];
            memset(writeSet, 0x00, transferLength);
            memset(readSet, 0x00, transferLength);
            for (int c = 0; c < message->size(); c++) {
                writeSet[c] = message->at(c);
            };
            spi_write_read_blocking(spi0, (uint8_t*)writeSet, (uint8_t*)readSet, transferLength);
            string readable(readSet);
            printf(readSet);
        } catch (...) {
            printf("Error thrown in spi transfer");
        }
    }
};