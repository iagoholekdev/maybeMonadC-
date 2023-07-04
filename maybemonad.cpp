#include <iostream>
#include <functional>
#include <optional>

class Maybe {
private:
    std::optional<int> value;

public:
    Maybe(std::optional<int> value) : value(value) {}

    static Maybe unit(int value) {
        return Maybe(std::optional<int>(value));
    }

    template<typename Func>
    Maybe bind(Func func) const {
        if (value.has_value()) {
            return func(*value);
        } else {
            return Maybe(std::nullopt);
        }
    }

    Maybe sum() const {
        if (value.has_value()) {
            return Maybe(std::optional<int>(*value + 1));
        } else {
            return Maybe(std::nullopt);
        }
    }

    Maybe subtract() const {
        if (value.has_value()) {
            return Maybe(std::optional<int>(*value - 1));
        } else {
            return Maybe(std::nullopt);
        }
    }

    Maybe treatEmpty() const {
        if (!value.has_value()) {
            return Maybe(std::optional<int>(0));
        } else {
            return Maybe(value);
        }
    }

    std::optional<int> getValue() const {
        return value;
    }
};

Maybe operator+(const Maybe& m1, const Maybe& m2) {
    if (m1.getValue().has_value() && m2.getValue().has_value()) {
        return Maybe(std::optional<int>(*m1.getValue() + *m2.getValue()));
    } else {
        return Maybe(std::nullopt);
    }
}

int main() {
    Maybe m = Maybe::unit(5);
    Maybe result1 = m.bind([](int value) {
        return Maybe::unit(value + 50);
    });

    Maybe resultSum = m.bind([](int value) {
        return Maybe::unit(value).sum();
    });

    std::cout << "Result: ";
    if (resultSum.getValue().has_value()) {
        std::cout << *resultSum.getValue() << std::endl;
        std::cout << *result1.getValue() << std::endl;
    } else {
        std::cout << "Null" << std::endl;
    }

    return 0;
}
