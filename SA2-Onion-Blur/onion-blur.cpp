#include "pch.h"

static void __cdecl DrawMotion_Onion(NJS_MOTION* motion, NJS_OBJECT* obj, float frame)
{
	const auto frame_count = static_cast<float>(motion->nbFrame);

	const NJS_ARGB color_orig = GlobalSpriteColor;
	SaveConstantAttr();
	SaveControl3D();

	OnControl3D(nj_control_3d_flag_ & 0xFFFFFDDF | NJD_CONTROL_3D_CNK_BLEND_MODE | NJD_CONTROL_3D_CNK_CONSTANT_ATTR | NJD_CONTROL_3D_CONSTANT_MATERIAL);
	AddConstantAttrSADX(0, 2048); //2048 IS ALPHA IN SA2

	njColorBlendingMode(NJD_COLOR_BLENDING_SRCALPHA, NJD_SOURCE_COLOR);
	njColorBlendingMode(NJD_COLOR_BLENDING_ONE, NJD_DESTINATION_COLOR);

	float alpha = 0.75f;

	for (int i = 0; i < 2; ++i)
	{
		SetMaterial(alpha, 1.0, 1.0, 1.0);

		alpha -= 0.25f;
		frame -= 2.0f;

		if (frame < 0.0f)
		{
			frame = frame_count + frame;
		}

		DrawMotionAndObject(motion, obj, frame);
	}

	ResetMaterial();
	LoadControl3D();
	GlobalSpriteColor = color_orig;
	LoadConstantAttr();
}

void DrawSonicMotion(NJS_MOTION* Motion, NJS_OBJECT* obj, float frame)
{
	DrawMotionAndObject(Motion, obj, frame);

	if (SonicCO2PtrExtern && SonicCO2PtrExtern->base.AnimInfo.Current == 10)
		DrawMotion_Onion(Motion, obj, frame);
}

static void __declspec(naked) DrawSonicMotion_Asm()
{
	__asm
	{
		push[esp + 08h]
		push[esp + 08h]
		push ecx
		call DrawSonicMotion
		pop ecx
		add esp, 4
		add esp, 4
		retn
	}
}


DataPointer(KnucklesCharObj2*, KnuxCharObj2Ptr, 0x1A51C88);

extern "C" {


	__declspec(dllexport) void __cdecl DrawKnuxMotion(NJS_MOTION* Motion, NJS_OBJECT* obj, float frame)
	{
		DrawMotionAndObject(Motion, obj, frame);

		if (KnuxCharObj2Ptr && KnuxCharObj2Ptr->base.AnimInfo.Current == 10)
			DrawMotion_Onion(Motion, obj, frame);
	}

}

static void __declspec(naked) DrawKnuxMotion_Asm()
{
	__asm
	{
		push[esp + 08h]
		push[esp + 08h]
		push ecx
		call DrawKnuxMotion
		pop ecx
		add esp, 4
		add esp, 4
		retn
	}
}


void init_OnionBlur()
{
	WriteCall((void*)0x720687, DrawSonicMotion_Asm);
	WriteCall((void*)0x72F4A0, DrawKnuxMotion_Asm);
}