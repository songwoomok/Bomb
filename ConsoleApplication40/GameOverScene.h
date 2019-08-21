#pragma once
#include "Scene.h"

class GameOverScene : public Scene
{
public:
	GameOverScene(class SceneManager* a_pParent);
	virtual ~GameOverScene();

	virtual eScene GetScene() const override;

	virtual void Update(float a_fDeltaTime) override;
	virtual void Render() override;
};
