void drawImageAtPoint(Image image, uint8_t rotation)
{
    setRotation(rotation);

    Point startPoint = image.drawPoint;
    Point endPoint = {0, 0};

    switch (rotation)
    {
    case SCREEN_HORIZONTAL_1:
    case SCREEN_HORIZONTAL_2:
        endPoint.x = startPoint.x + image.width - 1;
        endPoint.y = startPoint.y + image.height;
        break;
    case SCREEN_VERTICAL_1:
    case SCREEN_VERTICAL_2:
        endPoint.x = startPoint.y + image.height - 1;
        endPoint.y = startPoint.x + image.width;
        break;
    }

    ILI9341_Set_Address(startPoint.x, startPoint.y, endPoint.x, endPoint.y);

    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

    unsigned char Temp_small_buffer[BURST_MAX_SIZE];
    uint32_t counter = 0;
    for (uint32_t i = 0; i < image.width * image.height * 2 / BURST_MAX_SIZE; i++)
    {
        for (uint32_t k = 0; k < BURST_MAX_SIZE; k++)
        {
            Temp_small_buffer[k] = image.imageArray[counter + k];
        }
        HAL_SPI_Transmit(HSPI_INSTANCE, (unsigned char *)Temp_small_buffer, BURST_MAX_SIZE, 10);
        counter += BURST_MAX_SIZE;
    }
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}