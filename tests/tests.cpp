#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <type_traits>
#include <sstream>  // for operator<< test

#include "functions.h"
#include "student.h"

//------------------------------------------------------------------------------
// Compile-time Rule-of-Five checks
//------------------------------------------------------------------------------

static_assert(std::is_nothrow_destructible<student>::value,
              "student destructor must be noexcept");
static_assert(std::is_nothrow_copy_constructible<student>::value,
              "student copy constructor must be noexcept");
static_assert(std::is_nothrow_copy_assignable<student>::value,
              "student copy assignment must be noexcept");
static_assert(std::is_nothrow_move_constructible<student>::value,
              "student move constructor must be noexcept");

//------------------------------------------------------------------------------
// Helper: produces a sample student (homework grades 1–5, exam grade = 8)
//------------------------------------------------------------------------------

static student makeSampleStudent() {
    return student("Alice", "Smith",
                   {1, 2, 3, 4, 5},  // all within 1–10
                   8);                // exam also 1–10
}

////////////////////////////////////////////////////////////////////////////////
// Copy‐Constructor Tests
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("student copy-constructor copies data correctly") {
    student original = makeSampleStudent();
    original.skaiciuotiGalutini('v');
    float expV = original.getGalutinisV();
    float expM = original.getGalutinisM();

    student copy = original;

    CHECK(copy.getVardas()     == original.getVardas());
    CHECK(copy.getPavarde()    == original.getPavarde());
    CHECK(copy.getGalutinisV() == doctest::Approx(expV));
    CHECK(copy.getGalutinisM() == doctest::Approx(expM));

    // original still intact
    CHECK(original.getVardas()  == "Alice");
    CHECK(original.getPavarde() == "Smith");
}

////////////////////////////////////////////////////////////////////////////////
// Copy‐Assignment Tests
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("student copy-assignment copies data correctly") {
    student original = makeSampleStudent();
    original.skaiciuotiGalutini('v');
    float expV = original.getGalutinisV();
    float expM = original.getGalutinisM();

    student target("Bob", "Brown", {1,1,1,1,1}, 5);
    CHECK_NOTHROW(target = original);

    CHECK(target.getVardas()     == original.getVardas());
    CHECK(target.getPavarde()    == original.getPavarde());
    CHECK(target.getGalutinisV() == doctest::Approx(expV));
    CHECK(target.getGalutinisM() == doctest::Approx(expM));
}

TEST_CASE("copy-assignment returns *this by reference") {
    student src = makeSampleStudent();
    student dst("Bob","Brown",{1,1,1,1,1},5);

    student &ref = (dst = src);
    CHECK(&ref == &dst);
}

////////////////////////////////////////////////////////////////////////////////
// Move‐Assignment Tests
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("move-assignment moves all fields correctly") {
    student src   = makeSampleStudent();
    src.skaiciuotiGalutini('v');
    double expV   = src.getGalutinisV();
    double expM   = src.getGalutinisM();

    student dst("Bob", "Brown", {1,1,1,1,1}, 5);
    CHECK_NOTHROW(dst = std::move(src));

    CHECK(dst.getVardas()     == "Alice");
    CHECK(dst.getPavarde()    == "Smith");
    CHECK(dst.getGalutinisV() == doctest::Approx(expV));
    CHECK(dst.getGalutinisM() == doctest::Approx(expM));
}

TEST_CASE("move-assignment returns *this by reference") {
    student src = makeSampleStudent();
    student dst("Bob", "Brown", {1,1,1,1,1}, 5);

    student &ref = (dst = std::move(src));
    CHECK(&ref == &dst);
}

////////////////////////////////////////////////////////////////////////////////
// Move‐Constructor Tests
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("student move-constructor moves data correctly") {
    student tmp = makeSampleStudent();
    tmp.skaiciuotiGalutini('v');
    std::string expName    = tmp.getVardas();
    std::string expSurname = tmp.getPavarde();
    float       expV       = tmp.getGalutinisV();
    float       expM       = tmp.getGalutinisM();

    student dst(std::move(tmp));

    CHECK(dst.getVardas()     == expName);
    CHECK(dst.getPavarde()    == expSurname);
    CHECK(dst.getGalutinisV() == doctest::Approx(expV));
    CHECK(dst.getGalutinisM() == doctest::Approx(expM));

    // moved-from tmp still safe to query
    (void)tmp.getVardas();
    (void)tmp.getPavarde();
}

////////////////////////////////////////////////////////////////////////////////
// Average & Median Calculation Tests
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("skaiciuotiVid() on empty grades returns 0.0f") {
    student s{"A","B",{}, 5};
    CHECK(s.skaiciuotiVid() == doctest::Approx(0.0f));
}

TEST_CASE("skaiciuotiVid() computes correct average") {
    // grades within 1–10: {2,4,6} → avg = 4
    student s{"A","B",{2,4,6}, 5};
    CHECK(s.skaiciuotiVid() == doctest::Approx(4.0f));
}

TEST_CASE("skaiciuotiMed() on empty grades returns 0.0f") {
    student s{"A","B",{}, 5};
    CHECK(s.skaiciuotiMed() == doctest::Approx(0.0f));
}

TEST_CASE("skaiciuotiMed() computes correct median for odd count") {
    student s{"A","B",{5,1,9}, 5};
    CHECK(s.skaiciuotiMed() == doctest::Approx(5.0f));
}

TEST_CASE("skaiciuotiMed() computes correct median for even count") {
    student s{"A","B",{8,2,4,10}, 5};
    CHECK(s.skaiciuotiMed() == doctest::Approx(6.0f));
}

////////////////////////////////////////////////////////////////////////////////
// Final Grade Calculation Tests
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("skaiciuotiGalutini('v') sets galutinisV correctly") {
    student s{"A","B",{10,6}, 5};
    s.skaiciuotiGalutini('v');
    CHECK(s.getGalutinisV() == doctest::Approx(6.2f));
}

TEST_CASE("skaiciuotiGalutini('m') sets galutinisM correctly") {
    student s{"A","B",{8,2,4,10}, 5};
    s.skaiciuotiGalutini('m');
    CHECK(s.getGalutinisM() == doctest::Approx(5.4f));
}

////////////////////////////////////////////////////////////////////////////////
// Stream‐Output Operator Tests
////////////////////////////////////////////////////////////////////////////////

TEST_CASE("operator<< produces expected formatted string") {
    student s{"Jane","Doe",{1,2,3}, 5};
    s.skaiciuotiGalutini('v');
    std::ostringstream oss;
    oss << s;
    std::string out = oss.str();

    CHECK(out.find("Vardas: Jane") != std::string::npos);
    CHECK(out.find("Pavarde: Doe")  != std::string::npos);
    CHECK(out.find("1 2 3")         != std::string::npos);
    CHECK(out.find("Egzaminas: 5")  != std::string::npos);
    CHECK(out.find("Galutinis(V):") != std::string::npos);
}
