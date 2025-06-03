#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "..\UnitTests\doctest.h"
#include "..\main\Product.cpp"
#include "..\main\StorageUnit.cpp"
#include "..\main\Warehouse.cpp"
#include "..\main\Section.cpp"
#include "..\main\Shelf.cpp"
#include "..\main\Number.cpp"
#include "..\main\ChangeLog.cpp"
#include <iostream>
#include <sstream>

TEST_SUITE("ProductTests") {
    TEST_CASE("Empty constructor") {
        std::string name = "";
        struct tm enDate = struct tm();
        struct tm exDate = struct tm();
        std::string manufacturer = "";
        double quantity = 0.0;
        std::string measurementUnit = "Kilograms";
        std::string comment = "";

        Product p;

        std::string productName = p.getName();
        struct tm productEnDate = p.getEntDate();
        struct tm productExpDate = p.getEntDate();
        std::string productManufacturer = p.getManufacturer();
        double productQuantity = p.getQuantity();
        std::string productMeasurementUnit = p.stringMeasurementUnit();
        std::string productComment = p.getComment();

        CHECK_EQ(name, productName);
        CHECK_EQ(enDate.tm_year, productEnDate.tm_year);
        CHECK_EQ(exDate.tm_year, productExpDate.tm_year);
        CHECK_EQ(manufacturer, productManufacturer);
        CHECK(quantity == productQuantity);
        CHECK_EQ(measurementUnit, productMeasurementUnit);
        CHECK_EQ(comment, productComment);
    }

    TEST_CASE("String constructor") {
            std::string name = "Milk";
            std::string enDate = "2025-1-1";
            std::string exDate = "2025-1-10";
            std::string manufacturer = "Pilos";
            std::string quantity = "2.000000";
            std::string measurementUnit = "Litres";
            std::string comment = "Just milk";

            SUBCASE("Invalid name")
            {
                CHECK_THROWS(Product("", enDate, exDate, manufacturer, quantity, measurementUnit, comment));
            }
            SUBCASE("Invalid enter date")
            {
                CHECK_THROWS(Product(name, "", exDate, manufacturer, quantity, measurementUnit, comment));
            }
            SUBCASE("Invalid expiration date")
            {
                CHECK_THROWS(Product(name, enDate, "", manufacturer, quantity, measurementUnit, comment));
            }
            SUBCASE("Invalid manufacturer")
            {
                CHECK_THROWS(Product(name, enDate, exDate, "", quantity, measurementUnit, comment));
            }
            SUBCASE("Invalid quantity")
            {
                CHECK_THROWS(Product(name, enDate, exDate, manufacturer, "", measurementUnit, comment));
            }
            SUBCASE("Invalid measurement unit")
            {
                CHECK_THROWS(Product(name, enDate, exDate, manufacturer, quantity, "", comment));
            }
            SUBCASE("Proper initialization")
            {
                Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);

                std::string productName = p.getName();

                std::stringstream ss1;
                ss1 << p.getEntDate().tm_year + 1900 << "-" << p.getEntDate().tm_mon + 1 << "-" << p.getEntDate().tm_mday;
                std::string productEnDate = ss1.str();

                std::stringstream ss2;
                ss2 << p.getExpDate().tm_year + 1900 << "-" << p.getExpDate().tm_mon + 1 << "-" << p.getExpDate().tm_mday;
                std::string productExpDate = ss2.str();

                std::string productManufacturer = p.getManufacturer();
                std::string productQuantity = std::to_string(p.getQuantity());
                std::string productMeasurementUnit = p.stringMeasurementUnit();
                std::string productComment = p.getComment();

                CHECK_EQ(name, productName);
                CHECK_EQ(enDate, productEnDate);
                CHECK_EQ(exDate, productExpDate);
                CHECK_EQ(manufacturer, productManufacturer);
                CHECK_EQ(quantity, productQuantity);
                CHECK_EQ(measurementUnit, productMeasurementUnit);
                CHECK_EQ(comment, productComment);
            }
    }

    TEST_CASE("Name getter") {
        std::string name = "Milk";
        std::string enDate = "2025-1-01";
        std::string exDate = "2025-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);

        std::string productName = p.getName();
        CHECK_EQ(name, productName);
    }

    TEST_CASE("Enter date getter") {
        std::string name = "Milk";
        std::string enDate = "2025-1-1";
        std::string exDate = "2025-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);

        std::stringstream ss1;
        ss1 << p.getEntDate().tm_year +1900<< "-" << p.getEntDate().tm_mon +1 << "-" << p.getEntDate().tm_mday;
        std::string productEnDate = ss1.str();
        CHECK_EQ(enDate, productEnDate);
    }

    TEST_CASE("Expiration date getter") {
        std::string name = "Milk";
        std::string enDate = "2025-1-1";
        std::string exDate = "2025-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);

        std::stringstream ss1;
        ss1 << p.getExpDate().tm_year +1900 << "-" << p.getExpDate().tm_mon + 1 << "-" << p.getExpDate().tm_mday;
        std::string productExpDate = ss1.str();
        CHECK_EQ(exDate, productExpDate);
    }

    TEST_CASE("Manufacturer getter") {
        std::string name = "Milk";
        std::string enDate = "2025-1-01";
        std::string exDate = "2025-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);

        std::string productManufacturer = p.getManufacturer();
        CHECK_EQ(manufacturer, productManufacturer);
    }

    TEST_CASE("Quantity getter") {
        std::string name = "Milk";
        std::string enDate = "2025-1-01";
        std::string exDate = "2025-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);

        double productQuantity = p.getQuantity();
        CHECK_EQ(2.0, productQuantity);
    }

    TEST_CASE("Measurement unit as string (like a getter)") {
        std::string name = "Milk";
        std::string enDate = "2025-1-01";
        std::string exDate = "2025-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);

        std::string productMeasurementUnit = p.stringMeasurementUnit();
        CHECK_EQ(measurementUnit, productMeasurementUnit);
    }

    TEST_CASE("Comment getter") {
        std::string name = "Milk";
        std::string enDate = "2025-1-01";
        std::string exDate = "2025-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);

        std::string productComment = p.getComment();
        CHECK_EQ(comment, productComment);
    }

    TEST_CASE("NumberId setter & getter") {
        Product p;

        SUBCASE("Throws error if lower than 0 or more than the available numbers (10)")
        {
            CHECK_THROWS(p.setNumberId(-1));
            CHECK_THROWS(p.setNumberId(11));
        }
        SUBCASE("Should return 0")
        {
            p.setNumberId(0);
            CHECK_EQ(0, p.getNumberId());
        }
    }

    TEST_CASE("ShelfId setter & getter") {
        Product p;

        SUBCASE("Throws error if lower than 0 or more than the available shelves (10)")
        {
            CHECK_THROWS(p.setShelfId(-1));
            CHECK_THROWS(p.setShelfId(11));
        }
        SUBCASE("Should return 0")
        {
            p.setShelfId(0);
            CHECK_EQ(0, p.getShelfId());
        }
    }

    TEST_CASE("SectionId setter & getter") {
        Product p;

        SUBCASE("Throws error if lower than 0 or more than the available sections (10)")
        {
            CHECK_THROWS(p.setSectionId(-1));
            CHECK_THROWS(p.setSectionId(11));
        }
        SUBCASE("Should return 0")
        {
            p.setSectionId(0);
            CHECK_EQ(0, p.getSectionId());
        }
    }

    TEST_CASE("Close to expiration") {
        std::string name = "Milk";
        std::string enDate = "2024-1-01";
        std::string exDate = "2026-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p1(name, enDate, enDate, manufacturer, quantity, measurementUnit, comment);
        Product p2(name, exDate, exDate, manufacturer, quantity, measurementUnit, comment);

        SUBCASE("Is expired")
        {
            CHECK(p1.closeToExpiration());
        }
        SUBCASE("Isn't expired")
        {
            CHECK(!p2.closeToExpiration());
        }
    }

    TEST_CASE("Reduce quantity by")
    {
        std::string name = "Milk";
        std::string enDate = "2024-1-01";
        std::string exDate = "2026-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);

        SUBCASE("Removes some quantity")
        {
            p.reduceQuantityBy(1);
            CHECK_EQ(1, p.getQuantity());
        }
        SUBCASE("Removes all quantity (amount needed is more than total)")
        {
            p.reduceQuantityBy(3);
            CHECK_EQ(0, p.getQuantity());
        }
    }

    TEST_CASE("Operator == & !=")
    {
        std::string name = "Milk";
        std::string enDate = "2024-1-01";
        std::string exDate = "2026-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p1(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);
        Product p2;
        Product p3;

        SUBCASE("The two are equal")
        {
            CHECK(p2==p3);
            CHECK(!(p2 != p3));
        }
        SUBCASE("The two are different")
        {
            CHECK(!(p1 == p2));
            CHECK(p1 != p2);
        }
    }

    TEST_CASE("Operator <")
    {
        std::string name1 = "Apple";
        std::string name2 = "Milk";
        std::string enDate = "2024-1-01";
        std::string exDate1 = "2026-1-10";
        std::string exDate2 = "2026-1-12";
        std::string manufacturer = "Pilos";
        std::string quantity1 = "2.000000";
        std::string quantity2 = "3.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p1(name1, enDate, exDate1, manufacturer, quantity1, measurementUnit, comment);
        Product p2(name1, enDate, exDate1, manufacturer, quantity2, measurementUnit, comment);
        Product p3(name1, enDate, exDate2, manufacturer, quantity2, measurementUnit, comment);
        Product p4(name2, enDate, exDate1, manufacturer, quantity2, measurementUnit, comment);

        SUBCASE("Products with different names")
        {
            CHECK(p1 < p4);
        }
        SUBCASE("Same products (name and exp. date) with different quantities")
        {
            CHECK(p1 < p2);
        }
        SUBCASE("Same products (name, quantity doesnt matter) with different exp. dates")
        {
            CHECK(p1 < p3);
        }
    }

    TEST_CASE("Product to string")
    {
        std::string name = "Milk";
        std::string enDate = "2024-1-01";
        std::string exDate = "2026-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p1(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);
        std::string expectedOutput = "Milk|2024-1-1|2026-1-10|Pilos|-1/-1/-1|2|Litres|Just milk";

        std::string productString = p1.productToString();

        CHECK_EQ(expectedOutput, productString);
    }

    TEST_CASE("Product as a message")
    {
        std::string name = "Milk";
        std::string enDate = "2024-1-01";
        std::string exDate = "2026-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p1(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);
        std::string expectedOutput = "Product Milk that entered on 2024-1-1 and expires on 2026-1-10 from manufacturer Pilos with location: SectionId: -1, ShelfId: -1, with NumberId: -1 with quantity of 2 Litres (Just milk)";

        std::string productMessage = p1.productAsMessage();

        CHECK_EQ(expectedOutput, productMessage);
    }

    TEST_CASE("Operator <<")
    {
        Product p;
        std::ostringstream ss;

        ss << p;
        std::string expectedOutput = "|1900-1-0|1900-1-0||-1/-1/-1|0|Kilograms|\n";

        CHECK_EQ(expectedOutput, ss.str());
    }

    TEST_CASE("Operator >>")
    {
        Product p;
        std::istringstream ss("Milk|2024-1-1|2026-1-10|Pilos|0/0/0|2|Litres|Just milk");

        ss >> p;

        CHECK_EQ(ss.str(), p.productToString());
    }
}

TEST_SUITE("WarehouseTests")
{
    TEST_CASE("Clone function") {
        Warehouse w;
        CHECK_NOTHROW(StorageUnit * iw = w.clone(); delete iw;);
    }
    TEST_CASE("Add")
    {
        Warehouse w;

        std::string name = "Milk";
        std::string enDate = "2025-1-1";
        std::string exDate1 = "2025-1-10";
        std::string exDate2 = "2026-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p1(name, enDate, exDate1, manufacturer, quantity, measurementUnit, comment);
        Product p2(name, enDate, exDate2, manufacturer, quantity, measurementUnit, comment);
        SUBCASE("general add")
        {
            w.add(&p1);
            CHECK(w.getSections()[0].getShelves()[0].getNumbers()[0].getProducts().size() == 1);
        }
        SUBCASE("add with the same type of product")
        {
            w.add(&p1);
            w.add(&p1);
            CHECK(w.getSections()[0].getShelves()[0].getNumbers()[0].getProducts().size() == 2);
        }
        SUBCASE("add on a full number")
        {
            w.add(&p1);
            w.add(&p2);
            CHECK(w.getSections()[0].getShelves()[0].getNumbers()[0].getProducts().size() == 1);
            CHECK(w.getSections()[0].getShelves()[0].getNumbers()[1].getProducts().size() == 1);
        }
    }
    TEST_CASE("Print") {
        Warehouse w;

        std::string name = "Milk";
        std::string enDate = "2025-1-01";
        std::string exDate = "2025-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);

        std::string expectedOutput = "Product Milk that entered on 2025-1-1 and expires on 2025-1-10 from manufacturer Pilos with location: SectionId: 0, ShelfId: 0, with NumberId: 0 with quantity of 2 Litres (Just milk)\nMilk: 2 Litres\n";

        std::ostringstream ss;

        w.add(&p);
        w.print(ss);

        CHECK_EQ(expectedOutput, ss.str());
    }
    TEST_CASE("Print product list") {
        Warehouse w;

        std::string name = "Milk";
        std::string enDate = "2025-1-01";
        std::string exDate = "2025-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);
        
        std::string expectedOutput = "Milk|2025-1-1|2025-1-10|Pilos|0/0/0|2|Litres|Just milk\n";

        std::ostringstream ss;

        w.add(&p);
        w.printProductList(ss);

        CHECK_EQ(expectedOutput, ss.str());
    }
    TEST_CASE("Copy constructor")
    {
        Warehouse w;
        Product p;
        w.add(&p);
        Warehouse wa(w);
        std::string expectedOutput = "|1900-1-0|1900-1-0||0/0/0|0|Kilograms|\n";
        std::ostringstream ss;
        ss << wa;
        CHECK_EQ(expectedOutput, ss.str());
    }
    TEST_CASE("Operator =")
    {
        Warehouse w;
        Product p;
        w.add(&p);
        Warehouse wa = w;
        std::string expectedOutput = "|1900-1-0|1900-1-0||0/0/0|0|Kilograms|\n";
        std::ostringstream ss;
        ss << wa;
        CHECK_EQ(expectedOutput, ss.str());
    }
    TEST_CASE("Operator >>")
    {
        Warehouse w;
        std::string expectedOutput = "Milk|2024-1-1|2026-1-10|Pilos|0/0/0|2|Litres|Just milk\n";
        std::istringstream ss1(expectedOutput);
        ss1 >> w;
        std::ostringstream ss2;
        ss2 << w;
        CHECK_EQ(expectedOutput, ss2.str());
    }
    TEST_CASE("Operator <<")
    {
        Warehouse w;
        Product p;
        w.add(&p);
        std::string expectedOutput = "|1900-1-0|1900-1-0||0/0/0|0|Kilograms|\n";
        std::ostringstream ss;
        ss << w;
        CHECK_EQ(expectedOutput, ss.str());
    }
    TEST_CASE("Add directly")
    {
        std::string name = "Milk";
        std::string enDate = "2024-1-01";
        std::string exDate = "2026-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);

        p.setSectionId(0);
        p.setShelfId(0);
        p.setNumberId(0);

        Warehouse w;
        std::string expectedOutput = "Milk|2024-1-1|2026-1-10|Pilos|0/0/0|2|Litres|Just milk\n";

        bool didAdd = w.addDirectly(&p);

        CHECK(didAdd);

        std::ostringstream ss;

        w.printProductList(ss);

        CHECK_EQ(expectedOutput, ss.str());
    }
    TEST_CASE("Log")
    {
        Product p;
        Warehouse w;
        
        std::time_t now = std::time(0);
        struct tm time;
        localtime_s(&time, &now);

        std::stringstream ss1;

        ss1 << time.tm_year + 1900 << "-" << time.tm_mon + 1 << "-" << time.tm_mday;

        SUBCASE("log addition")
        {
            w.add(&p);
            std::string expectedOutput = ss1.str() + " add product Product  that entered on 1900-1-0 and expires on 1900-1-0 from manufacturer  with location: SectionId: 0, ShelfId: 0, with NumberId: 0 with quantity of 0 Kilograms ()\n";

            std::ostringstream ss2;

            w.log("2024-1-1", "2026-1-1", ss2);
            CHECK_EQ(expectedOutput, ss2.str());
        }
    }
    TEST_CASE("Remove")
    {
        std::string name = "Milk";
        std::string enDate = "2024-1-01";
        std::string exDate = "2026-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);
        Warehouse w;
        w.add(&p);

        SUBCASE("quantity needed is less than present - should only change the quantity of the product")
        {
            w.remove("Milk",1);
            double changedQuantity = w.getSections()[0].getShelves()[0].getNumbers()[0].getProducts()[0]->getQuantity();
            CHECK_EQ(1.0, changedQuantity);
        }
        SUBCASE("quantity needed is equal to present - should remove the product")
        {
            w.remove("Milk", 2);
            Number num = w.getSections()[0].getShelves()[0].getNumbers()[0];
            bool isEmpty = num.getProducts().size() == 0;
            CHECK(isEmpty);
        }
    }
    TEST_CASE("Clean")
    {
        Product p;
        Warehouse w;

        w.add(&p);
        w.clean();

        CHECK(w.getSections()[0].getShelves()[0].getNumbers()[0].getProducts().size() == 0);
    }
    TEST_CASE("Check losses")
    {
        std::string name = "Milk";
        std::string enDate = "2024-1-1";
        std::string exDate = "2026-1-10";
        std::string manufacturer = "Pilos";
        std::string quantity = "2.000000";
        std::string measurementUnit = "Litres";
        std::string comment = "Just milk";

        Product p(name, enDate, exDate, manufacturer, quantity, measurementUnit, comment);
        Warehouse w;

        std::string expectedOutput = "Money lost: 6\n";
        std::ostringstream ss;

        w.add(&p);
        w.check_losses(name, 3, 2, "2024-1-1", "2027-1-01", std::cout);
        w.check_losses(name, 3, 2, "2024-1-1", "2027-1-01",ss);
        std::string actualOutput = ss.str();
        CHECK_EQ(expectedOutput, actualOutput);
    }
}