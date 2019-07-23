#include "graphics.h"
#include "rapidxml.hpp"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> //std::reverse

using namespace rapidxml;

namespace bones
{
	static std::string get_spritesheet_path(std::string file_contents);
	static std::string open_file_as_string(std::string filepath);
	static std::vector<Frame> load_frames_from_xml(std::string file_contents);
	static Frame create_frame_from_xml_node(xml_node<>* frame_node);
	static SDL_Rect read_rect(xml_node<>* node);
	static std::vector<SDL_Rect> read_multiple_rects(xml_node<>* node);
	static std::string get_attribute_from_node(std::string name, xml_node<>* node);

	GraphicsLoader::GraphicsLoader(SDL_Renderer* renderer)
	{
		if (renderer == nullptr)
			throw std::runtime_error("SDL_Renderer is invalid.");
		this->renderer = renderer;
	}

	Sprite GraphicsLoader::load_sprite(std::string filepath)
	{
		std::shared_ptr<SDL_Texture> texture;
		if (is_texture_in_registry(filepath))
		{
			texture = get_loaded_texture(filepath);
		}
		else
		{
			texture = load_new_texture(filepath);
			registry[filepath] = texture;
		}
		return Sprite(texture);
	}

	bool GraphicsLoader::is_texture_in_registry(std::string filepath)
	{
		return registry.find(filepath) != registry.end();
	}

	std::shared_ptr<SDL_Texture> GraphicsLoader::get_loaded_texture(std::string filepath)
	{
		return registry.at(filepath);
	}

	std::shared_ptr<SDL_Texture> GraphicsLoader::load_new_texture(std::string filepath)
	{
		SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
		if (!surface)
		{
			return nullptr;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 160, 96, 128));
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (!texture)
		{
			return nullptr;
		}
		SDL_FreeSurface(surface);

		auto destructor = [](SDL_Texture * tex) { SDL_DestroyTexture(tex); };
		return std::shared_ptr<SDL_Texture>(texture, destructor);
	}


	Animation GraphicsLoader::load_animation(std::string filepath)
	{
		auto file_content = open_file_as_string(filepath);
		auto frames = load_frames_from_xml(file_content);
		auto sheetpath = get_spritesheet_path(file_content);
		Sprite spritesheet = load_sprite(sheetpath);
		return Animation(spritesheet, frames);
	}

	static std::string get_spritesheet_path(std::string file_contents)
	{
		xml_document<> doc;
		doc.parse<0>(&(file_contents[0])); // parse doesn't like const char * so give it char*
		xml_node<>* root = doc.first_node();

		return get_attribute_from_node("spritesheet", root);
	}

	static std::string open_file_as_string(std::string filepath)
	{
		std::ifstream in(filepath);
		if (!in)
		{
			throw std::runtime_error("Could not open animation file: " + filepath);
		}

		std::stringstream ss;
		ss << in.rdbuf();
		in.close();
		std::string data(ss.str());
		return data;
	}

	static std::vector<Frame> load_frames_from_xml(std::string file_contents)
	{
		xml_document<> doc;
		doc.parse<0>(&(file_contents[0])); // parse doesn't like const char * so give it char*
		xml_node<>* root = doc.first_node();

		std::vector<Frame> frames;
		for (xml_node<>* frame_node = root->first_node(); frame_node; frame_node = frame_node->next_sibling())
		{
			Frame frame = create_frame_from_xml_node(frame_node);
			frames.push_back(frame);
		}
		return frames;
	}

	static Frame create_frame_from_xml_node(xml_node<>* frame_node)
	{
		xml_node<>* hitboxes = frame_node->first_node("hitboxes");
		xml_node<>* dmgboxes = frame_node->first_node("damageboxes");

		Frame frame;
		frame.duration = std::stoi(get_attribute_from_node("duration", frame_node));
		frame.sheet_clip = read_rect(frame_node);

		if (hitboxes)
			frame.hitboxes = read_multiple_rects(hitboxes);
		if (dmgboxes)
			frame.damageboxes = read_multiple_rects(dmgboxes);

		return frame;
	}

	static std::vector<SDL_Rect> read_multiple_rects(xml_node<>* node)
	{
		std::vector<SDL_Rect> rects;
		if (node && node->first_node())
		{
			for (xml_node<>* box = node->first_node(); node; node = node->next_sibling())
			{
				auto rect = read_rect(box);
				rects.push_back(rect);
			}
		}
		return rects;
	}

	static SDL_Rect read_rect(xml_node<>* node)
	{
		int x = std::stoi(get_attribute_from_node("x", node));
		int y = std::stoi(get_attribute_from_node("y", node));
		int w = std::stoi(get_attribute_from_node("w", node));
		int h = std::stoi(get_attribute_from_node("h", node));
		return SDL_Rect{ x, y, w, h };
	}

	static std::string get_attribute_from_node(std::string name, xml_node<>* node)
	{
		if (node && node->first_attribute(name.c_str()))
		{
			return node->first_attribute(name.c_str())->value();
		}
		throw std::runtime_error("Attribute does not exist!");
	}
}