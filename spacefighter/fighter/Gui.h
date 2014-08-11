#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

namespace gui {
	class Element : public sf::Drawable {
	public:
		virtual sf::Vector2f calculateSize() const = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};

	class Invisible : public Element {
	public:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const { /* draw nothing */ }
		virtual sf::Vector2f calculateSize() const { return sf::Vector2f(0.0f, 0.0f);/* has no size*/ }

	};

	class Image : public Element {
	protected:
		sf::Sprite mSprite;
		sf::Texture mTexture;
	public:
		Image(const std::string& path);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(mSprite, states); }
		virtual sf::Vector2f calculateSize() const { return sf::Vector2f(mSprite.getTexture()->getSize()); }
	};

	class TextBased : public Element {
	protected:
		sf::Text mText;
	public:
		TextBased(const std::string& text);
		void setText(const std::string& text) { mText.setString(text); onTextChanged(text); }
		const std::string& getText() const { return mText.getString(); }
		virtual sf::Vector2f calculateSize() const { return sf::Vector2f(mText.getLocalBounds().width, mText.getLocalBounds().height); }

		virtual void onTextChanged(const std::string& text) {}
	};

	class Progress : public TextBased {
	protected:
		float mValue;
	public:
		inline void setValue(float value) { mValue = value; }
		inline float getValue() const { return mValue; }
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
	};

	class Check : public TextBased {
	protected:
		bool mChecked;
	public:
		inline bool isChecked() const { return mChecked; }
		inline void setChecked(bool checked) { mChecked = checked; }
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

	class ButtonListener {
	public:
		virtual void onButtonEvent();
	};

	class Button : public TextBased {
	protected:
		static sf::Texture sTexture;
		sf::Sprite mSprite;
	public:
		Button(const std::string& text = "");
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void onPositionChanged(const sf::Vector2f& position);
		virtual sf::Vector2f calculateSize() const { return sf::Vector2f(sTexture.getSize().x, sTexture.getSize().y); }

	};

	class Input : public TextBased {
	protected:
		bool mReadOnly;
	public:
		void setReadOnly(bool readOnly) { mReadOnly = readOnly; }
		bool isReadOnly() const { return mReadOnly; }
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

	class Text : public TextBased {
	public:
		Text(const std::string& text = "");
		virtual void onTextChanged(const std::string& text) {}
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

	class Container : public Element {
	public:
		enum Layout { FLOW, ROW, MATRIX };

		Container();
		void setLayout(Layout layout) { mLayout = layout; }
		Layout getLayout() const { return mLayout; }

		void add(Element& element) { add(&element); }
		void add(Element* element) { mChildren.push_back(element); }
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setPadding(const sf::Vector2f& padding) { mPadding = padding; }
		void setSpacing(const sf::Vector2f& spacing) { mSpacing = spacing; }
		const sf::Vector2f& getPadding() const { return mPadding; }
		virtual sf::Vector2f calculateSize() const;

	protected:
		Layout mLayout;
		sf::Vector2f mPadding;
		sf::Vector2f mSpacing;
		std::vector<Element*> mChildren;
	};

	class Frame : public Container {
	protected:
		sf::Sprite mSprites[3][3];
		sf::Texture mTexture;
		sf::Vector2f mBorder;
		sf::VertexArray mVertices;
	public:
		Frame();
		void prepare();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		inline void setBorder(const sf::Vector2f& border) { mBorder = border; }
		inline const sf::Vector2f& getBorder()const{ return mBorder; }
		virtual sf::Vector2f calculateSize() const;
	};

	class Window : public Frame {
	protected:
		sf::Text mCaption;
	public:
		Window();
		void setCaption(const std::string& caption) { mCaption.setString(caption); }
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	};

	class Gui {
	protected:
		sf::Font mFont;
		static Gui sInstance;
	public:
		inline sf::Font& getFont() { return mFont; }
		void loadResources();
		inline static Gui& getInstance() { return sInstance; }

	};
}