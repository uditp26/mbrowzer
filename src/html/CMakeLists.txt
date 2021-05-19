cmake_minimum_required(VERSION 3.20.1)

set(this src_html)

set(html_sources
    Parser.cpp
)

add_library(${this} STATIC ${html_sources} ${html_headers})