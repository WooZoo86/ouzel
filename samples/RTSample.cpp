// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "RTSample.h"
#include "MainMenu.h"

using namespace std;
using namespace ouzel;

RTSample::RTSample(Samples& aSamples):
    samples(aSamples)
{
    eventHandler.gamepadHandler = bind(&RTSample::handleGamepad, this, placeholders::_1, placeholders::_2);
    eventHandler.uiHandler = bind(&RTSample::handleUI, this, placeholders::_1, placeholders::_2);
    eventHandler.keyboardHandler = bind(&RTSample::handleKeyboard, this, placeholders::_1, placeholders::_2);
    sharedEngine->getEventDispatcher()->addEventHandler(&eventHandler);

    rtLayer = std::make_shared<scene::Layer>();
    addLayer(rtLayer);

    std::shared_ptr<graphics::Texture> renderTarget(new graphics::Texture());
    renderTarget->init(Size2(256.0f, 256.0f), true, false, true, 1, false);
    renderTarget->setClearColor(Color(0, 64, 0));

    rtCamera = std::make_shared<scene::Camera>();
    rtCamera->setRenderTarget(renderTarget);

    rtLayer->addCamera(rtCamera);

    camera1 = std::make_shared<scene::Camera>();
    camera1->setScaleMode(scene::Camera::ScaleMode::SHOW_ALL);
    camera1->setTargetContentSize(Size2(400.0f, 600.0f));
    camera1->setViewport(Rectangle(0.0f, 0.0f, 0.5f, 1.0f));

    camera2 = std::make_shared<scene::Camera>();
    camera2->setScaleMode(scene::Camera::ScaleMode::SHOW_ALL);
    camera2->setTargetContentSize(Size2(400.0f, 600.0f));
    camera2->setViewport(Rectangle(0.5f, 0.0f, 0.5f, 1.0f));

    layer = std::make_shared<scene::Layer>();
    layer->addCamera(camera1);
    layer->addCamera(camera2);
    addLayer(layer);

    characterSprite = std::make_shared<ouzel::scene::Sprite>("run.json");
    characterSprite->play(true);

    rtCharacter = std::make_shared<scene::Node>();
    rtCharacter->addComponent(characterSprite);

    rtLayer->addChild(rtCharacter);

    scene::SpriteFrame rtFrame(renderTarget, Rectangle(0.0f, 0.0f, 256.0f, 256.0f), false, renderTarget->getSize(), Vector2(), Vector2(0.5f, 0.5f));

    std::vector<scene::SpriteFrame> spriteFrames = {rtFrame};
    rtSprite = std::make_shared<scene::Sprite>();
    rtSprite->initFromSpriteFrames(spriteFrames);
    rtNode = std::make_shared<scene::Node>();
    rtNode->addComponent(rtSprite);
    layer->addChild(rtNode);

    guiCamera = std::make_shared<scene::Camera>();
    guiCamera->setScaleMode(scene::Camera::ScaleMode::SHOW_ALL);
    guiCamera->setTargetContentSize(Size2(800.0f, 600.0f));

    guiLayer = std::make_shared<scene::Layer>();
    guiLayer->addCamera(guiCamera);
    addLayer(guiLayer);

    menu = std::make_shared<gui::Menu>();
    guiLayer->addChild(menu);

    backButton = std::make_shared<ouzel::gui::Button>("button.png", "button_selected.png", "button_down.png", "", "Back", "arial.fnt", Color::BLACK, Color::BLACK, Color::BLACK);
    backButton->setPosition(Vector2(-200.0f, -200.0f));
    menu->addWidget(backButton);
}

bool RTSample::handleGamepad(Event::Type type, const GamepadEvent& event)
{
    if (type == Event::Type::GAMEPAD_BUTTON_CHANGE)
    {
        if (event.pressed &&
            event.button == input::GamepadButton::B)
        {
            samples.setScene(std::shared_ptr<scene::Scene>(new MainMenu(samples)));
        }
    }

    return true;
}

bool RTSample::handleUI(Event::Type type, const UIEvent& event) const
{
    if (type == Event::Type::UI_CLICK_NODE && event.node == backButton)
    {
        samples.setScene(std::shared_ptr<scene::Scene>(new MainMenu(samples)));
    }

    return true;
}

bool RTSample::handleKeyboard(Event::Type type, const KeyboardEvent& event) const
{
    if (type == Event::Type::KEY_DOWN)
    {
        switch (event.key)
        {
            case input::KeyboardKey::ESCAPE:
                samples.setScene(std::shared_ptr<scene::Scene>(new MainMenu(samples)));
                break;
            default:
                break;
        }
    }
    
    return true;
}
