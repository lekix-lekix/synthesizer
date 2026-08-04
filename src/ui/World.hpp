#pragma once
#include <QObject>
#include <QQmlEngine>
#include <QPointF>
#include <iostream>

class World : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF pan READ getPan WRITE setPan NOTIFY panChanged)

public:
    explicit World(QObject *parent = nullptr) : QObject(parent) {
        std::cout << "world constructed at " << this << std::endl;
    }

    inline static World *s_instance = nullptr;

    static World &instance() {
        Q_ASSERT(s_instance);
        return *s_instance;
    }

    int     gridSize            = { 128 };
    int     worldWidthUnits     = { 300 };
    int     worldHeightUnits    = { 200 };
    float   zoom                = { 1 };
    QPointF pan                 = { 0, 0 };

    Q_INVOKABLE QPoint coordToPx(QPoint coord);
    Q_INVOKABLE QPointF pxToCoord(QPoint px);
    Q_INVOKABLE void calculateNewPan(QPoint mousePos, QPoint mouseInitPos);

    Q_INVOKABLE QPointF getPan() { return this->pan; }
    World const &setPan(QPointF newPan) { pan = newPan; return *this; }

signals:
    void panChanged();
};

// --- Separate foreign registration type ---
struct WorldForeign
{
    Q_GADGET
    QML_FOREIGN(World)
    QML_SINGLETON
    QML_NAMED_ELEMENT(World)

public:
    static World *create(QQmlEngine *, QJSEngine *engine)
    {
        std::cout << "create called" << std::endl;
        Q_ASSERT(World::s_instance);
        Q_ASSERT(engine->thread() == World::s_instance->thread());
        if (s_engine)
            Q_ASSERT(engine == s_engine);
        else
            s_engine = engine;

        QQmlEngine::setObjectOwnership(World::s_instance, QQmlEngine::CppOwnership);
        return World::s_instance;
    }

private:
    inline static QJSEngine *s_engine = nullptr;
};