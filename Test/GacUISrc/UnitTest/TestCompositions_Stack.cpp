#include "TestCompositions.h"
using namespace composition_bounds_tests;

TEST_FILE
{
	TEST_CATEGORY(L"Test <Stack> with common <Bounds> operations")
	{
		TestBoundsWithTrivialChildren<GuiBoundsComposition>();
	});

	TEST_CASE(L"Test <Stack> with <StackItem>")
	{
		auto stack = new GuiStackComposition;

		stack->SetMinSizeLimitation(GuiGraphicsComposition::LimitToElementAndChildren);
		stack->SetPreferredMinSize(Size(50, 50));

		TEST_ASSERT(stack->GetExtraMargin() == Margin(0, 0, 0, 0));
		TEST_ASSERT(stack->GetPadding() == 0);
		stack->SetExtraMargin(Margin(11, 22, 33, 44));
		stack->SetPadding(10);
		TEST_ASSERT(stack->GetExtraMargin() == Margin(11, 22, 33, 44));
		TEST_ASSERT(stack->GetPadding() == 10);

		GuiStackItemComposition* stackItems[3];
		const vint ITEM_COUNT = sizeof(stackItems) / sizeof(*stackItems);
		for (vint i = 0; i < ITEM_COUNT; i++)
		{
			stackItems[i] = new GuiStackItemComposition;
			stackItems[i]->SetPreferredMinSize(Size(100 + i * 10, 100 + i * 20));
			stack->InsertStackItem(i, stackItems[i]);
		}

		{
			TEST_ASSERT(stack->GetDirection() == GuiStackComposition::Horizontal);
			TEST_ASSERT(stack->GetClientArea() == Rect({ 0,0 }, { 64 + 330,66 + 140 }));
			TEST_ASSERT(stack->GetMinPreferredClientSize() == stack->GetClientArea().GetSize());
			TEST_ASSERT(stack->GetPreferredBounds() == stack->GetClientArea());
			TEST_ASSERT(stack->GetBounds() == stack->GetClientArea());
			for (vint i = 0; i < ITEM_COUNT; i++)
			{
				vint offset = 11 + (100 + 10) * i + 10 * i * (i - 1) / 2;
				TEST_ASSERT(stackItems[i]->GetBounds() == Rect({ offset,22 }, { 100 + i * 10,140 }));
			}

			stack->SetDirection(GuiStackComposition::ReversedHorizontal);
			TEST_ASSERT(stack->GetDirection() == GuiStackComposition::ReversedHorizontal);
			TEST_ASSERT(stack->GetClientArea() == Rect({ 0,0 }, { 64 + 330,66 + 140 }));
			TEST_ASSERT(stack->GetMinPreferredClientSize() == stack->GetClientArea().GetSize());
			TEST_ASSERT(stack->GetPreferredBounds() == stack->GetClientArea());
			TEST_ASSERT(stack->GetBounds() == stack->GetClientArea());
			for (vint i = 0; i < ITEM_COUNT; i++)
			{
				vint offset = 33 + (100 + 10) * i + 10 * i * (i - 1) / 2;
				offset = 64 + 330 - offset - (100 + i * 10);
				TEST_ASSERT(stackItems[i]->GetBounds() == Rect({ offset,22}, {100 + i * 10,140}));
			}

			stack->SetDirection(GuiStackComposition::Vertical);
			TEST_ASSERT(stack->GetDirection() == GuiStackComposition::Vertical);
			auto fuck = stack->GetClientArea();
			TEST_ASSERT(stack->GetClientArea() == Rect({ 0,0 }, { 44 + 120,86 + 360 }));
			TEST_ASSERT(stack->GetMinPreferredClientSize() == stack->GetClientArea().GetSize());
			TEST_ASSERT(stack->GetPreferredBounds() == stack->GetClientArea());
			TEST_ASSERT(stack->GetBounds() == stack->GetClientArea());
			for (vint i = 0; i < ITEM_COUNT; i++)
			{
				vint offset = 22 + (100 + 10) * i + 20 * i * (i - 1) / 2;
				TEST_ASSERT(stackItems[i]->GetBounds() == Rect({ 11,offset }, { 120,100 + i * 20 }));
			}

			stack->SetDirection(GuiStackComposition::ReversedVertical);
			TEST_ASSERT(stack->GetDirection() == GuiStackComposition::ReversedVertical);
			TEST_ASSERT(stack->GetClientArea() == Rect({ 0,0 }, { 44 + 120,86 + 360 }));
			TEST_ASSERT(stack->GetMinPreferredClientSize() == stack->GetClientArea().GetSize());
			TEST_ASSERT(stack->GetPreferredBounds() == stack->GetClientArea());
			TEST_ASSERT(stack->GetBounds() == stack->GetClientArea());
			for (vint i = 0; i < ITEM_COUNT; i++)
			{
				vint offset = 44 + (100 + 10) * i + 20 * i * (i - 1) / 2;
				offset = 86 + 360 - offset - (100 + i * 20);
				TEST_ASSERT(stackItems[i]->GetBounds() == Rect({ 11,offset }, { 120,100 + i * 20 }));
			}
		}

		for (vint i = 0; i < ITEM_COUNT; i++)
		{
			Margin extraMargin(1 * i, 2 * i, 3 * i, 4 * i);
			stackItems[i]->SetExtraMargin(extraMargin);
			TEST_ASSERT(stackItems[i]->GetExtraMargin() == extraMargin);
		}

		{
			stack->SetDirection(GuiStackComposition::Horizontal);
			TEST_ASSERT(stack->GetDirection() == GuiStackComposition::Horizontal);
			TEST_ASSERT(stack->GetClientArea() == Rect({ 0,0 }, { 64 + 330,66 + 140 }));
			TEST_ASSERT(stack->GetMinPreferredClientSize() == stack->GetClientArea().GetSize());
			TEST_ASSERT(stack->GetPreferredBounds() == stack->GetClientArea());
			TEST_ASSERT(stack->GetBounds() == stack->GetClientArea());
			for (vint i = 0; i < ITEM_COUNT; i++)
			{
				vint offset = 11 + (100 + 10) * i + 10 * i * (i - 1) / 2;
				TEST_ASSERT(stackItems[i]->GetBounds() == Rect({ offset - 1 * i,22 - 2 * i }, { 100 + i * 10 + 4 * i,140 + 6 * i }));
			}

			stack->SetDirection(GuiStackComposition::ReversedHorizontal);
			TEST_ASSERT(stack->GetDirection() == GuiStackComposition::ReversedHorizontal);
			TEST_ASSERT(stack->GetClientArea() == Rect({ 0,0 }, { 64 + 330,66 + 140 }));
			TEST_ASSERT(stack->GetMinPreferredClientSize() == stack->GetClientArea().GetSize());
			TEST_ASSERT(stack->GetPreferredBounds() == stack->GetClientArea());
			TEST_ASSERT(stack->GetBounds() == stack->GetClientArea());
			for (vint i = 0; i < ITEM_COUNT; i++)
			{
				vint offset = 33 + (100 + 10) * i + 10 * i * (i - 1) / 2;
				offset = 64 + 330 - offset - (100 + i * 10);
				TEST_ASSERT(stackItems[i]->GetBounds() == Rect({ offset - 1 * i,22 - 2 * i }, { 100 + i * 10 + 4 * i,140 + 6 * i }));
			}

			stack->SetDirection(GuiStackComposition::Vertical);
			TEST_ASSERT(stack->GetDirection() == GuiStackComposition::Vertical);
			auto fuck = stack->GetClientArea();
			TEST_ASSERT(stack->GetClientArea() == Rect({ 0,0 }, { 44 + 120,86 + 360 }));
			TEST_ASSERT(stack->GetMinPreferredClientSize() == stack->GetClientArea().GetSize());
			TEST_ASSERT(stack->GetPreferredBounds() == stack->GetClientArea());
			TEST_ASSERT(stack->GetBounds() == stack->GetClientArea());
			for (vint i = 0; i < ITEM_COUNT; i++)
			{
				vint offset = 22 + (100 + 10) * i + 20 * i * (i - 1) / 2;
				TEST_ASSERT(stackItems[i]->GetBounds() == Rect({ 11 - 1 * i,offset - 2 * i }, { 120 + 4 * i,100 + i * 20 + 6 * i }));
			}

			stack->SetDirection(GuiStackComposition::ReversedVertical);
			TEST_ASSERT(stack->GetDirection() == GuiStackComposition::ReversedVertical);
			TEST_ASSERT(stack->GetClientArea() == Rect({ 0,0 }, { 44 + 120,86 + 360 }));
			TEST_ASSERT(stack->GetMinPreferredClientSize() == stack->GetClientArea().GetSize());
			TEST_ASSERT(stack->GetPreferredBounds() == stack->GetClientArea());
			TEST_ASSERT(stack->GetBounds() == stack->GetClientArea());
			for (vint i = 0; i < ITEM_COUNT; i++)
			{
				vint offset = 44 + (100 + 10) * i + 20 * i * (i - 1) / 2;
				offset = 86 + 360 - offset - (100 + i * 20);
				TEST_ASSERT(stackItems[i]->GetBounds() == Rect({ 11 - 1 * i,offset - 2 * i }, { 120 + 4 * i,100 + i * 20 + 6 * i }));
			}
		}

		SafeDeleteComposition(stack);
	});

	TEST_CASE(L"Test <Stack> with clipped <StackItem>")
	{
	});
}