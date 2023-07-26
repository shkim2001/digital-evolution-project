#ifndef TASK_H
#define TASK_H

#include <cmath>
#include <string>

/**
  * Basic base task class
  */
class Task {
public:
  virtual double CheckOutput(uint32_t output, uint32_t inputs[4]) = 0;
  virtual std::string name() const = 0;
  virtual int id() const = 0;
  virtual ~Task() { }
};

/**
  * NOT task -- did they calculate NOT of a number?
  */
class NOT : public Task {
public:
  double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
    // did they calculate NOT of a number?
    for (int i = 0; i < 4; i++) {
      uint32_t not_val = ~inputs[i]; //~ is bitwise NOT in C++
      if (not_val == output) {
        return 30.0;
      }
    }
    // 0 points for failure
    return 0.0;
  }

  std::string name() const override { return "NOT"; }
  int id() const override { return 0; }
};

/**
  * NAND task -- did they calculate NOT of a number?
  */
class NAND : public Task {
public:
  double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
    // did they calculate NOT of a number?
    for (int i = 0; i < 4; i++) {
      uint32_t x = inputs[i];
      uint32_t y;
      if (i < 3) y = inputs[i + 1];
      else y = inputs[0];
      uint32_t result = ~(x & y);
      if (result == output) {
        return 15.0;
      }
    }
    return 0.0;
  }

  std::string name() const override { return "NAND"; }
  int id() const override { return 1; }
};

/**
  * AND task -- x & y
  */
class AND : public Task {
public:
  double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
    // did they calculate NOT of a number?
    for (int i = 0; i < 4; i++) {
      uint32_t x = inputs[i];
      uint32_t y;
      if (i < 3) y = inputs[i + 1];
      else y = inputs[0];
      uint32_t result = (x & y);
      if (result == output) {
        return 15.0;
      }
    }
    // 0 points for failure
    return 0.0;
  }

  std::string name() const override { return "AND"; }
  int id() const override { return 2; }
};

/**
  * ORN task -- x | ~y
  */
class ORN: public Task {
public:
  double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
    // did they calculate NOT of a number?
    for (int i = 0; i < 4; i++) {
      uint32_t x = inputs[i];
      uint32_t y;
      if (i < 3) y = inputs[i + 1];
      else y = inputs[0];
      uint32_t result = x | ~y;
      if (result == output) {
        return 15.0;
      }
    }
    return 0.0;
  }

  std::string name() const override { return "ORN"; }
  int id() const override { return 3; }
};

/**
  * OR task -- x | y
  */
class OR : public Task {
public:
  double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
    // did they calculate NOT of a number?
    for (int i = 0; i < 4; i++) {
      uint32_t x = inputs[i];
      uint32_t y;
      if (i < 3) y = inputs[i + 1];
      else y = inputs[0];
      uint32_t result = x | y;
      if (result == output) {
        return 15.0;
      }
    }
    // 0 points for failure
    return 0.0;
  }

  std::string name() const override { return "OR"; }
  int id() const override { return 4; }
};

/**
  * ANDN task -- x & ~y
  */
class ANDN : public Task {
public:
  double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
    // did they calculate NOT of a number?
    for (int i = 0; i < 4; i++) {

      uint32_t x = inputs[i];
      uint32_t y;
      if (i < 3) y = inputs[i + 1];
      else y = inputs[0];
      uint32_t result = (x & ~y);
      if (result == output) {
        return 15.0;
      }
    }
    // 0 points for failure
    return 0.0;
  }

  std::string name() const override { return "ANDN"; }
  int id() const override { return 5; }
};

/**
  * NOR  task -- ~(x | y)
  */
class NOR : public Task {
public:
  double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
    // did they calculate NOT of a number?
    for (int i = 0; i < 4; i++) {
      uint32_t x = inputs[i];
      uint32_t y;
      if (i < 3) y = inputs[i + 1];
      else y = inputs[0];
      uint32_t result = ~x | y;
      if (result == output) {
        return 15.0;
      }
    }
    // 0 points for failure
    return 0.0;
  }

  std::string name() const override { return "NOR"; }
  int id() const override { return 6; }
};

/**
  * XOR task -- x ^ y
  */
class XOR : public Task {
public:
  double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
    // did they calculate NOT of a number?
    for (int i = 0; i < 4; i++) {
      uint32_t x = inputs[i];
      uint32_t y;
      if (i < 3) y = inputs[i + 1];
      else y = inputs[0];
      uint32_t result = x ^ y;
      if (result == output) {
        return 15.0;
      }
    }
    // 0 points for failure
    return 0.0;
  }

  std::string name() const override { return "XOR"; }
  int id() const override { return 7; }
};

/**
  * EQU task -- ~(x^ y)
  */
class EQU : public Task {
public:
  double CheckOutput(uint32_t output, uint32_t inputs[4]) override {
    for (int i = 0; i < 4; i++) {
      uint32_t x = inputs[i];
      uint32_t y;
      if (i < 3) y = inputs[i + 1];
      else y = inputs[0];
      uint32_t result = ~(x ^ y);
      if (result == output) {
        return 15.0;
      }
    }
    // 0 points for failure
    return 0.0;
  }

  std::string name() const override { return "EQU"; }
  int id() const override { return 8; }
};

#endif
