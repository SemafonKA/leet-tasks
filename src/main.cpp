#include <format>
#include <iostream>
#include <list>

class IObserver {
 public:
  virtual void update() = 0;
};

class IObservable {
 public:
  void addObserver(IObserver *observer) { _observers.push_back(observer); }

  void notifyUpdate() {
    for (auto &observer : _observers) {
      observer->update();
    }
  }

 private:
  std::list<IObserver *> _observers;
};

class TemperatureModel : public IObservable {
 public:
  float getF() { return _temperatureF; }
  float getC() { return (_temperatureF - 32.0) * 5.0 / 9.0; }

  void setF(float tempF) {
    _temperatureF = tempF;
    notifyUpdate();
  }

  void setC(float tempC) {
    _temperatureF = tempC * 9.0 / 5.0 + 32.0;
    notifyUpdate();
  }

 private:
  float _temperatureF;
};

class ConsoleView : public IObserver {
 public:
  ConsoleView(TemperatureModel *model) {
    _model = model;
    _model->addObserver(this);
  }

  virtual void update() {
    using std::cout;
    using std::format;

    system("clear");
    cout << format("Temperature in Celsius: {:0.2f}\n", _model->getC());
    cout << format("Temperature in Farenheit: {:0.2f}\n", _model->getF());
    cout << "Input temperature in Celsius: ";
  }

 private:
  TemperatureModel *_model;
};

class Controller {
 public:
  Controller(TemperatureModel *model) { _model = model; }

  void start() {
    _model->setC(0);

    float temp = 0;
    do {
      std::cin >> temp;
      _model->setC(temp);
    } while (temp != 0);
  }

 private:
  TemperatureModel *_model;
};

int main() {
  TemperatureModel model;
  ConsoleView view(&model);
  Controller controller(&model);

  controller.start();
  return 0;
}

