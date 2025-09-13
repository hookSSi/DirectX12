#include "core/common/d3dApp.h"
#include <DirectXColors.h>

using namespace DirectX;

class AppInitializer : public D3DApp
{
    public:
        explicit AppInitializer(HINSTANCE hInstance);
        ~AppInitializer() override;

        bool Initialize() override;

    private:
        void OnResize() override;
        void Update(const Common::GameTimer &gameTimer) override;
        void Draw(const Common::GameTimer &gameTimer) override;
};