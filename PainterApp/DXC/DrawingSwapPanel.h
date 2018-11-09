#pragma once

#include "pch.h"
#include <d2d1_2.h> 
#include <concrt.h> 

namespace DXC
{
	[Windows::Foundation::Metadata::WebHostHidden]
    public ref class DrawingSwapPanel sealed : public Windows::UI::Xaml::Controls::SwapChainPanel
    {
	public:
		DrawingSwapPanel();
	protected private:
		bool	m_loadingComplete; // загрузка завершена
		float	m_renderTargetHeight;
		float	m_renderTargetWidth;

		float	m_compositionScaleX;
		float	m_compositionScaleY;

		float	m_height;
		float	m_width;

		D2D1_COLOR_F m_backgroundColor;
		// Resources 3D
		Microsoft::WRL::ComPtr<ID3D11Device1>			m_d3dDevice; 
		Microsoft::WRL::ComPtr<ID3D11DeviceContext1>	m_d3dContext; 
		Microsoft::WRL::ComPtr<IDXGISwapChain2>			m_swapChain; 

		// Resources 2D
		Microsoft::WRL::ComPtr<ID2D1Factory2>			m_d2dFactory;
		Microsoft::WRL::ComPtr<ID2D1Device>				m_d2dDevice;
		Microsoft::WRL::ComPtr<ID2D1DeviceContext>		m_d2dContext;
		Microsoft::WRL::ComPtr<ID2D1Bitmap1>			m_d2dTargetBitmap;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>	m_whiteBrush;

		// Sync 
		Concurrency::critical_section m_criticalSection;
		DXGI_ALPHA_MODE m_alphaMode;

		// Init
		virtual void CreateDeviceResources();
		virtual void CreateDeviceIndependentResources();
		virtual void CreateSizeDependentResources();

		// События
		virtual void OnDeviceLost();
		virtual void OnSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e);
		virtual void OnCompositionScaleChanged(Windows::UI::Xaml::Controls::SwapChainPanel ^sender, Platform::Object ^args);
		virtual void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
		virtual void OnResuming(Platform::Object^ sender, Platform::Object^ args) { };

		// Рисовать
		virtual void Present();
		virtual void Render();
    };
}
