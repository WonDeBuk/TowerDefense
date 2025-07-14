#pragma once

#include "raylib.h"
#include <string>
#include <vector>

//static void DrawTextJustified(const std::string& Text, float TextWidth, float FontSize);
static void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);   // Draw text using font inside rectangle limits
static void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);

static void DrawTextJustified(Font font, const char* text, Vector2 position, float width, float fontSize, float spacing, Color tint, float lineSpacing = -1.0f, float minSpaceWidth = 5.0f) {
    // Default line spacing to font size if not specified
    if (lineSpacing < 0) lineSpacing = fontSize;
    // Starting draw position
    float posX = position.x;
    float posY = position.y;
    // Measure one space character width for normal (non-justified) spacing
    Vector2 spaceMeasure = MeasureTextEx(font, " ", fontSize, spacing);
    float spaceWidth = spaceMeasure.x;
    
    std::vector<std::string> lineWords;
    float lineWordsWidth = 0.0f;
    std::string word;

    // Helper lambda: draw the current line of words.
    // doJustify=true distributes extra space (full-justify), false leaves it left-aligned.
    auto drawLine = [&](bool doJustify) {
        if (lineWords.empty()) return;
        float x = posX;
        float y = posY;
        size_t n = lineWords.size();
        if (doJustify && n > 1) {
            // Compute total width of words
            float totalWordsW = 0.0f;
            for (const auto &w : lineWords) {
                Vector2 m = MeasureTextEx(font, w.c_str(), fontSize, spacing);
                totalWordsW += m.x;
            }
            float extraSpace = width - totalWordsW;
            int gaps = (int)n - 1;
            // Distribute extra space (as integer pixels)
            int totalExtra = (int)roundf(extraSpace);
            int baseGap = totalExtra / gaps;
            int remainder = totalExtra % gaps;
            // Draw each word, adding gap after each except last
            for (size_t i = 0; i < n; i++) {
                const std::string &w = lineWords[i];
                DrawTextEx(font, w.c_str(), { x, y }, fontSize, spacing, tint);
                float wW = MeasureTextEx(font, w.c_str(), fontSize, spacing).x;
                x += wW;
                if (i < n - 1) {
                    int gap = baseGap + ((int)i < remainder ? 1 : 0);
                    x += (float)gap;
                }
            }
        } else {
            // Left-align (no justification): one normal space between words
            for (size_t i = 0; i < n; i++) {
                const std::string &w = lineWords[i];
                DrawTextEx(font, w.c_str(), { x, y }, fontSize, spacing, tint);
                float wW = MeasureTextEx(font, w.c_str(), fontSize, spacing).x;
                x += wW;
                if (i < n - 1) x += spaceWidth;
            }
        }
    };
    
    // Process characters in text
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (c == '\n' || c == '\\') {
            // Explicit newline: add any pending word, then draw line (no justify)
            if (!word.empty()) {
                float wW = MeasureTextEx(font, word.c_str(), fontSize, spacing).x;
                if (lineWords.empty()) {
                    lineWords.push_back(word);
                    lineWordsWidth = wW;
                } else {
                    if (lineWordsWidth + wW + minSpaceWidth > width) {
                        drawLine(true);
                        posY += lineSpacing;
                        lineWords.clear();
                        lineWordsWidth = 0.0f;
                        lineWords.push_back(word);
                        lineWordsWidth = wW;
                    } else {
                        float newTotal = lineWordsWidth + wW;
                        int gaps = (int)lineWords.size();
                        float leftover = width - newTotal;
                        if (leftover / gaps < minSpaceWidth) {
                            drawLine(true);
                            posY += lineSpacing;
                            lineWords.clear();
                            lineWordsWidth = 0.0f;
                            lineWords.push_back(word);
                            lineWordsWidth = wW;
                        } else {
                            lineWords.push_back(word);
                            lineWordsWidth = newTotal;
                        }
                    }
                }
                word.clear();
            }
            // Draw the line (explicit break, so no justification)
            drawLine(false);
            posY += lineSpacing;
            lineWords.clear();
            lineWordsWidth = 0.0f;
        }
        else if (c == ' ') {
            // Space: end of current word
            if (!word.empty()) {
                float wW = MeasureTextEx(font, word.c_str(), fontSize, spacing).x;
                if (lineWords.empty()) {
                    lineWords.push_back(word);
                    lineWordsWidth = wW;
                } else {
                    // Check fit with minimum spacing
                    if (lineWordsWidth + wW + minSpaceWidth > width) {
                        // Word doesn't fit: wrap line before word
                        drawLine(true);
                        posY += lineSpacing;
                        lineWords.clear();
                        lineWordsWidth = 0.0f;
                        lineWords.push_back(word);
                        lineWordsWidth = wW;
                    } else {
                        // Check average gap if justified
                        float newTotal = lineWordsWidth + wW;
                        int gaps = (int)lineWords.size();
                        float leftover = width - newTotal;
                        if (leftover / gaps < minSpaceWidth) {
                            // Not enough space per gap: wrap line before word
                            drawLine(true);
                            posY += lineSpacing;
                            lineWords.clear();
                            lineWordsWidth = 0.0f;
                            lineWords.push_back(word);
                            lineWordsWidth = wW;
                        } else {
                            lineWords.push_back(word);
                            lineWordsWidth = newTotal;
                        }
                    }
                }
                word.clear();
            }
            // Ignore extra spaces
        }
        else {
            // Accumulate character into current word
            word.push_back(c);
        }
    }
    // End of text: add last word if any
    if (!word.empty()) {
        float wW = MeasureTextEx(font, word.c_str(), fontSize, spacing).x;
        if (lineWords.empty()) {
            lineWords.push_back(word);
            lineWordsWidth = wW;
        } else {
            if (lineWordsWidth + wW + minSpaceWidth > width) {
                drawLine(true);
                posY += lineSpacing;
                lineWords.clear();
                lineWordsWidth = 0.0f;
                lineWords.push_back(word);
                lineWordsWidth = wW;
            } else {
                float newTotal = lineWordsWidth + wW;
                int gaps = (int)lineWords.size();
                float leftover = width - newTotal;
                if (leftover / gaps < minSpaceWidth) {
                    drawLine(true);
                    posY += lineSpacing;
                    lineWords.clear();
                    lineWordsWidth = 0.0f;
                    lineWords.push_back(word);
                    lineWordsWidth = wW;
                } else {
                    lineWords.push_back(word);
                    lineWordsWidth = newTotal;
                }
            }
        }
        word.clear();
    }
    // Draw the final line (no justification on last line)
    if (!lineWords.empty()) {
        drawLine(false);
    }
}

static void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint)
{
    DrawTextBoxedSelectable(font, text, rec, fontSize, spacing, wordWrap, tint, 0, 0, WHITE, WHITE);
}

// Draw text using font inside rectangle limits with support for text selection
static void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint)
{
    int length = TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize/(float)font.baseSize;     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap? MEASURE_STATE : DRAW_STATE;

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
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;

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
                endLine = (endLine < 1)? i : endLine;
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
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize*scaleFactor) > rec.height) break;

                // Draw selection background
                bool isGlyphSelected = false;
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                {
                    DrawRectangleRec({ rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize*scaleFactor }, selectBackTint);
                    isGlyphSelected = true;
                }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    DrawTextCodepoint(font, codepoint, { rec.x + textOffsetX, rec.y + textOffsetY }, fontSize, isGlyphSelected? selectTint : tint);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
    }
}

// static void DrawTextJustified(const std::string& Text, float TextWidth, float FontSize) {
//     int TotalCodepoint = TextLength(&Text[0]);

//     float XOffset = 0.0f;
//     float YOffset = 0.0f;
//     float ScaleFactor = FontSize / 100.0f;
//     float GlyphWidth = 64.0f * ScaleFactor;
//     flaot GlyphHeight = 101

//     for (int i = 0; i < TotalCodepoint; i++)
//     {
//         /* code */
//     }
    
// }