#pragma once

#include "raylib.h"
#include <vector>
#include <string>

static void DrawTextJustified(Font font, const char* text, Vector2 position, float width, float fontSize, float spacing, Color tint, float lineSpacing = -1.0f)
{
    if (lineSpacing < 0.0f) lineSpacing = 0.2f * fontSize;

    if (font.texture.id == 0) font = GetFontDefault();  // Security check in case of not valid font

    int size = TextLength(text);    // Total size in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on linebreak '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize / font.baseSize;         // Character quad scaling factor

    std::vector<std::vector<int>> lineBuffer;
    std::vector<int> wordBuffer;

    bool draw = false;

    float glyphWidth = 0.0f;
    float spaceMargin = 0.0f;

    float totalWidth = 0.0f; //total width of a whole word

    for (int i = 0; i < size;)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        //std::cout << codepoint << ' ';
        if (codepoint != '\n' && codepoint != ' ')
        {
            glyphWidth = ((font.glyphs[index].advanceX == 0) ? font.recs[index].width : font.glyphs[index].advanceX) * scaleFactor;

            //std::cout << textOffsetX + totalWidth + glyphWidth << '&' << width << "\n";
            if (textOffsetX + totalWidth + glyphWidth > width && lineBuffer.size() == 0) //word splitting should only be considered when it is the only word on that line
            {
                //std::cout << "in\n";
                lineBuffer.push_back(wordBuffer);
                wordBuffer.clear();
                draw = true;
            }

            else if (textOffsetX + totalWidth + glyphWidth > width && lineBuffer.size() > 0) //end line if there is at least 2 words with one exceeding the width
            {
                float remainingSpace = width - textOffsetX;
                spaceMargin = spacing + ((lineBuffer.size() == 1) ? 0.0f : remainingSpace / (lineBuffer.size() - 1));
                draw = true;
            }

            else
            {
                i += codepointByteCount;
                totalWidth += glyphWidth + spacing;
                wordBuffer.push_back(codepoint);
            }
        }

        else if (codepoint == ' ')
        {
            i += codepointByteCount;
            textOffsetX += totalWidth;
            totalWidth = 0.0f;
            lineBuffer.push_back(wordBuffer);
            wordBuffer.clear();
        }



        else if (codepoint == '\n')
        {
            //std::cout << "in\n";
            //NOTE!: if \n is used in the string, make sure that it is not follow by a space
            //otherwise, this will break

            i += codepointByteCount;
            textOffsetX += totalWidth;
            totalWidth = 0.0f;
            lineBuffer.push_back(wordBuffer);
            wordBuffer.clear();

            float remainingSpace = width - textOffsetX;
            spaceMargin = spacing + ((lineBuffer.size() == 1) ? 0.0f : remainingSpace / (lineBuffer.size() - 1));

            draw = true;

        }

        if (draw == true)
        {

            textOffsetX = 0.0f;
            int lineSize = lineBuffer.size();
            for (int j = 0; j < lineSize; j++)
            {
                int wordSize = lineBuffer[j].size();
                for (int k = 0; k < wordSize; k++)
                {
                    int temp = GetGlyphIndex(font, lineBuffer[j][k]);
                    DrawTextCodepoint(font, lineBuffer[j][k], { position.x + textOffsetX, position.y + textOffsetY }, fontSize, tint);
                    textOffsetX += ((font.glyphs[temp].advanceX == 0) ? font.recs[temp].width * scaleFactor : font.glyphs[temp].advanceX * scaleFactor);
                    if (k + 1 < wordSize) textOffsetX += spacing;
                }
                textOffsetX += spaceMargin;
            }
            draw = false;
            spaceMargin = 0.0f;
            lineBuffer.clear();
            textOffsetY += fontSize + lineSpacing;
            textOffsetX = 0.0f;
        }
    }

    textOffsetX += totalWidth;
    lineBuffer.push_back(wordBuffer);
    wordBuffer.clear();

    float remainingSpace = width - textOffsetX;
    spaceMargin = spacing + ((lineBuffer.size() == 1) ? 0.0f : remainingSpace / (lineBuffer.size() - 1));
    //std::cout << width << ' ';
    //std::cout << remainingSpace << '|' << textOffsetX << '|' << spaceMargin * (lineBuffer.size() - 1) << std::endl;

    textOffsetX = 0.0f;
    int lineSize = lineBuffer.size();
    for (int j = 0; j < lineSize; j++)
    {
        int wordSize = lineBuffer[j].size();
        for (int k = 0; k < wordSize; k++)
        {
            int temp = GetGlyphIndex(font, lineBuffer[j][k]);
            DrawTextCodepoint(font, lineBuffer[j][k], { position.x + textOffsetX, position.y + textOffsetY }, fontSize, tint);
            textOffsetX += ((font.glyphs[temp].advanceX == 0) ? font.recs[temp].width * scaleFactor : font.glyphs[temp].advanceX * scaleFactor);
            if (k + 1 < wordSize) textOffsetX += spacing;
        }
        textOffsetX += spaceMargin;
    }
}

static void DrawTextBoxed(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);   // Draw text using font inside rectangle limits
static void DrawTextBoxedSelectable(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);    // Draw text using font inside rectangle limits with support for text selection

static void DrawTextBoxed(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint)
{
    DrawTextBoxedSelectable(font, text, rec, fontSize, spacing, wordWrap, tint, 0, 0, WHITE, WHITE);
}

// Draw text using font inside rectangle limits with support for text selection
static void DrawTextBoxedSelectable(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint)
{
    int length = TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0.0f;       // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize / (float)font.baseSize;     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap ? MEASURE_STATE : DRAW_STATE;

    int startLine = -1;         // Index where to begin drawing (where a line begins)
    int endLine = -1;           // Index where to stop drawing (where a line ends)
    int lastk = -1;             // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width * scaleFactor : font.glyphs[index].advanceX * scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container).
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container.
        if (state == MEASURE_STATE)
        {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width)
            {
                endLine = (endLine < 1) ? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize * scaleFactor) > rec.height) break;

                // Draw selection background
                bool isGlyphSelected = false;
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                {
                    DrawRectangleRec({ rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize* scaleFactor }, selectBackTint);
                    isGlyphSelected = true;
                }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    DrawTextCodepoint(font, codepoint, { rec.x + textOffsetX, rec.y + textOffsetY }, fontSize, isGlyphSelected ? selectTint : tint);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        textOffsetX += glyphWidth;
    }
}