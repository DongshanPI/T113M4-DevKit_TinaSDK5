$(call inherit-product-if-exists, target/allwinner/t113_s4-common/t113_s4-common.mk)

PRODUCT_PACKAGES +=

PRODUCT_COPY_FILES +=

PRODUCT_AAPT_CONFIG := large xlarge hdpi xhdpi
PRODUCT_AAPT_PERF_CONFIG := xhdpi
PRODUCT_CHARACTERISTICS := musicbox

PRODUCT_BRAND := allwinner
PRODUCT_NAME := t113_s4_devkit
PRODUCT_DEVICE := t113_s4-devkit
PRODUCT_MODEL := Allwinner t113_s4 devkit  board
