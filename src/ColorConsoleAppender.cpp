/*
 * ---- Call of Suli ----
 *
 * ColorConsoleAppender.cpp
 *
 * Created on: 2021. 11. 01.
 *     Author: Valaczka János Pál <valaczka.janos@piarista.hu>
 *
 * ColorConsoleAppender
 *
 *  This file is part of Call of Suli.
 *
 *  Call of Suli is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ColorConsoleAppender.h"
#include <iostream>

// Formatting codes
const std::string ColorConsoleAppender::reset = "\033[m";
const std::string ColorConsoleAppender::bold = "\033[1m";
const std::string ColorConsoleAppender::dark = "\033[2m";
const std::string ColorConsoleAppender::underline = "\033[4m";
const std::string ColorConsoleAppender::blink = "\033[5m";
const std::string ColorConsoleAppender::reverse = "\033[7m";
const std::string ColorConsoleAppender::concealed = "\033[8m";
const std::string ColorConsoleAppender::clear_line = "\033[K";

// Foreground colors
const std::string ColorConsoleAppender::black = "\033[30m";
const std::string ColorConsoleAppender::red = "\033[31m";
const std::string ColorConsoleAppender::green = "\033[32m";
const std::string ColorConsoleAppender::yellow = "\033[33m";
const std::string ColorConsoleAppender::blue = "\033[34m";
const std::string ColorConsoleAppender::magenta = "\033[35m";
const std::string ColorConsoleAppender::cyan = "\033[36m";
const std::string ColorConsoleAppender::white = "\033[37m";

/// Background colors
const std::string ColorConsoleAppender::on_black = "\033[40m";
const std::string ColorConsoleAppender::on_red = "\033[41m";
const std::string ColorConsoleAppender::on_green = "\033[42m";
const std::string ColorConsoleAppender::on_yellow = "\033[43m";
const std::string ColorConsoleAppender::on_blue = "\033[44m";
const std::string ColorConsoleAppender::on_magenta = "\033[45m";
const std::string ColorConsoleAppender::on_cyan = "\033[46m";
const std::string ColorConsoleAppender::on_white = "\033[47m";


ColorConsoleAppender::ColorConsoleAppender()
	: ConsoleAppender()
{
	m_levelColor.insert(Logger::Trace, white+dark);
	m_levelColor.insert(Logger::Debug, white);
	m_levelColor.insert(Logger::Info, cyan+bold);
	m_levelColor.insert(Logger::Warning, yellow+bold);
	m_levelColor.insert(Logger::Error, red+bold);
	m_levelColor.insert(Logger::Fatal, white+bold+on_red);
}

/**
 * @brief ColorConsoleAppender::append
 * @param timeStamp
 * @param logLevel
 * @param file
 * @param line
 * @param function
 * @param category
 * @param message
 */

void ColorConsoleAppender::append(const QDateTime &timeStamp, Logger::LogLevel logLevel, const char *file, int line, const char *function, const QString &category, const QString &message)
{
	const std::string &color = m_levelColor.value(logLevel);

	if (!color.empty())
		std::cerr << color;

	std::cerr << qPrintable(formattedString(timeStamp, logLevel, file, line, function, category, message));

	if (!color.empty())
		std::cerr << reset << clear_line;
}


/**
 * @brief ColorConsoleAppender::levelColor
 * @return
 */

const QHash<Logger::LogLevel, std::string> &ColorConsoleAppender::levelColor() const
{
	return m_levelColor;
}


/**
 * @brief ColorConsoleAppender::setLevelColor
 * @param level
 * @param color
 */

void ColorConsoleAppender::setLevelColor(const Logger::LogLevel &level, const std::string &color)
{
	m_levelColor.insert(level, color);
}


/**
 * @brief ColorConsoleAppender::levelColor
 * @param level
 * @return
 */

std::string ColorConsoleAppender::levelColor(const Logger::LogLevel &level) const
{
	return m_levelColor.value(level);
}

