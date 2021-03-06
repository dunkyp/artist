/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ARTIST_TEXT_LAYOUT_MARCH_17_2020)
#define ARTIST_TEXT_LAYOUT_MARCH_17_2020

#include <string_view>
#include <artist/font.hpp>
#include <artist/rect.hpp>
#include <artist/color.hpp>
#include <infra/utf8_utils.hpp>
#include <infra/support.hpp>
#include <memory>
#include <functional>

namespace cycfi::artist
{
   class canvas;
   class text_layout;

   class text_layout : non_copyable
   {
   public:
                           text_layout(font const& font_, std::string_view utf8);
                           text_layout(font const& font_, color c, std::string_view utf8);
                           text_layout(text_layout&& rhs) noexcept;
                           ~text_layout();

      struct line_info
      {
         float    offset;
         float    width;
      };

      struct flow_info
      {
         bool     justify;
         float    line_height;
         float    last_line_height;
      };

      using get_line_info = std::function<line_info(float y)>;
      static constexpr auto npos = std::size_t(-1);

      void                 text(std::string_view utf8);
      void                 flow(float width, bool justify = false);
      void                 flow(get_line_info const& glf, flow_info finfo);
      void                 draw(canvas& cnv, point p) const;
      void                 draw(canvas& cnv, float x, float y) const;

      std::size_t          num_lines() const;
      point                caret_point(std::size_t index) const;
      std::size_t          caret_index(float x, float y) const;
      std::size_t          caret_index(point p) const;

   private:

      class impl;
      using impl_ptr = std::unique_ptr<impl>;

      impl_ptr             _impl;
   };

   ////////////////////////////////////////////////////////////////////////////
   // Inlines
   ////////////////////////////////////////////////////////////////////////////
   inline void text_layout::draw(canvas& cnv, float x, float y) const
   {
      draw(cnv, { x, y });
   }

   inline std::size_t text_layout::caret_index(float x, float y) const
   {
      return caret_index({x, y});
   }
}

#endif
