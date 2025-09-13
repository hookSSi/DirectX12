#include "core/AppInitializer.h"

AppInitializer::AppInitializer(HINSTANCE hInstance) : D3DApp(hInstance) {}

AppInitializer::~AppInitializer() {}

bool AppInitializer::Initialize() { return D3DApp::Initialize(); }

void AppInitializer::OnResize() { D3DApp::OnResize(); }

void AppInitializer::Update(const Common::GameTimer &gameTimer) {}

void AppInitializer::Draw(const Common::GameTimer &gameTimer)
{
    // Reuse the memory associated with command recording.
    // We can only reset when the associated command lists have finished
    // execution on the GPU.
    ThrowIfFailed(mDirectCmdListAlloc->Reset());

    // A command list can be reset after it has been added to the command queue
    // via ExecuteCommandList.
    // Reusing the command list reuses memory.
    ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));

    // Indicate a state transition on the resource usage.
    CD3DX12_RESOURCE_BARRIER transitionBarrier =
        CD3DX12_RESOURCE_BARRIER::Transition(
            CurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT,
            D3D12_RESOURCE_STATE_RENDER_TARGET);
    mCommandList->ResourceBarrier(1, &transitionBarrier);

    // Set the viewport and scissor rect.  This needs to be reset whenever the
    // command list is reset.
    mCommandList->RSSetViewports(1, &mScreenViewport);
    mCommandList->RSSetScissorRects(1, &mScissorRect);

    // Clear the back buffer and depth buffer.
    mCommandList->ClearRenderTargetView(CurrentBackBufferView(),
                                        Colors::LightSteelBlue, 0, nullptr);
    mCommandList->ClearDepthStencilView(
        DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
        1.0f, 0, 0, nullptr);

    // Specify the buffers we are going to render to.
    D3D12_CPU_DESCRIPTOR_HANDLE currentBackBufferView = CurrentBackBufferView();
    D3D12_CPU_DESCRIPTOR_HANDLE depthStencilView = DepthStencilView();
    mCommandList->OMSetRenderTargets(1, &currentBackBufferView, true,
                                     &depthStencilView);

    // Indicate a state transition on the resource usage.
    CD3DX12_RESOURCE_BARRIER renderTargetToPresentBarrier =
        CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
                                             D3D12_RESOURCE_STATE_RENDER_TARGET,
                                             D3D12_RESOURCE_STATE_PRESENT);
    mCommandList->ResourceBarrier(1, &renderTargetToPresentBarrier);

    // Done recording commands.
    ThrowIfFailed(mCommandList->Close());

    // Add the command list to the queue for execution.
    ID3D12CommandList *cmdsLists[] = {mCommandList.Get()};
    mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

    // swap the back and front buffers
    ThrowIfFailed(mSwapChain->Present(0, 0));
    mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;

    // Wait until frame commands are complete.  This waiting is inefficient and
    // is done for simplicity.  Later we will show how to organize our rendering
    // code so we do not have to wait per frame.
    FlushCommandQueue();
}