#include <map>
#include "core/core.h"
#include "events/event.h"

/*
  Base class for all layers.
*/
class Layer {
  public:
    Layer() {}
    Layer(std::string _name)
      : m_name(_name) {};
    virtual ~Layer() {};
    std::string GetName() { return m_name; };
    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    virtual void OnInspect() {}
    virtual void OnEvent(NC::Event& _event) {}

    bool IsEnabled() const { return m_enabled; }
    void SetEnabled(bool _enabled) { m_enabled = _enabled; }

  protected:
      bool m_enabled = true;
      const std::string m_name;
};

/*
  A layerstack is a container for other layers for the engine.
*/
class CLayerStack {
  
  public:
    static CLayerStack& _INSTANCE_(){
        static CLayerStack instance;
        return instance;
    }

    void PushLayer(Layer* _layer) { 
      m_layers.emplace(m_layers.begin() + m_inserter, _layer);
      ++m_inserter;
    }

    void PushOverlay(Layer* _layer) {
      m_layers.emplace_back(_layer); 
    }

    void PopLayer(Layer* _layer) { 
      auto it = std::find(m_layers.begin(), m_layers.begin() + m_inserter, _layer);
      if (it != m_layers.begin() + m_inserter) {
        _layer->OnDetach();
        m_layers.erase(it);
        --m_inserter;
      }
    }

    void PopOverlay(Layer* _overlay) { 
      auto it = std::find(m_layers.begin() + m_inserter, m_layers.end(), _overlay);
      if (it != m_layers.end()) {
        _overlay->OnDetach();
        m_layers.erase(it);
      }
    }

    std::vector<Layer*>::iterator iterator;
    std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
    std::vector<Layer*>::iterator end()   { return m_layers.end(); }
    std::vector<Layer*>::reverse_iterator rbegin() { return m_layers.rbegin(); }
    std::vector<Layer*>::reverse_iterator rend() { return m_layers.rend(); }

    void Sort(const std::vector<std::string> &order);
    std::vector <std::string> GetSortingOrder();

  private:
    std::vector<Layer*> m_layers;
    unsigned int m_inserter = 0;

    CLayerStack() {
			m_inserter = 0;
    }

    ~CLayerStack() {
      for (auto* layer : m_layers) {
        layer->OnDetach();
        delete layer;
      }
    }

};
#define LayerStack CLayerStack::_INSTANCE_()

template<class T>
Layer* factory() {
  return new T();
}
typedef Layer* (*CLayerFactory)(void);

/*
  Contains all the registered factories, 
  they can be fetched to create actual instances.
*/
class CLayerRegistry {
public:
  CLayerRegistry() {}

  static CLayerRegistry& _INSTANCE_() {
    static CLayerRegistry instance;
    return instance;
  }

  void Add(std::string _name, CLayerFactory _factory){
    m_registered[_name] = _factory;
  }

  Layer* Produce(std::string _name)
  {
    nc_assert(m_registered[_name], "Requested layer does not exist!");
    return m_registered[_name]();
  }

private:
  std::map<std::string, CLayerFactory> m_registered;
};

#define LayerRegistry CLayerRegistry::_INSTANCE_()

/*
  Factory instance to be registered.
*/
class CLayerRegistrationInstance {
  public:
    CLayerRegistrationInstance() {}
    CLayerRegistrationInstance(std::string _name, CLayerFactory _factory){
      LayerRegistry.Add(_name, _factory);
    }
};

#define REGISTER_LAYER(_factory_name, _factory_type) \
    CLayerRegistrationInstance _registration_instance ## _factory_type(_factory_name, &factory<_factory_type>);
