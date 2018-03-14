cmark
=====
*CommonMark API*

[![Build Status](https://travis-ci.org/krakjoe/cmark.svg?branch=master)](https://travis-ci.org/krakjoe/cmark)
[![Coverage Status](https://coveralls.io/repos/github/krakjoe/cmark/badge.svg)](https://coveralls.io/github/krakjoe/cmark)

Requires
========

  * libcmark

Build
=====

  * `./configure --with-cmark=/path/to/cmark/install --with-php-config=/path/to/php-config`
  * `make install`

API
===

```
namespace CommonMark\Node {
	final class Document extends \CommonMark\Node {}
	final class BlockQuote extends \CommonMark\Node {}

	final class BulletList implements \CommonMark\Interfaces\IList {
		public function setTight();
		public function isTight();

		public function setDelimitPeriod();
		public function hasPeriodDelim() : bool;
		public function setDelimitParen();
		public function hasParenDelim() : bool;
	}

	final class OrderedList implements  \CommonMark\Interfaces\IList {
		public function getStart() : int;
		public function setStart(int $start);

		public function setTight();
		public function isTight();

		public function setDelimitPeriod();
		public function hasPeriodDelim() : bool;
		public function setDelimitParen();
		public function hasParenDelim() : bool;
	}

	final class Item extends \CommonMark\Node {}

	final class Text extends \CommonMark\Node {
		public function __construct(string $literal);

		public function setLiteral(string $ltieral) : Text;
		public function getLiteral() : ?string;
	}

	final class Code extends Text {}
	final class CodeBlock extends Text {}
	final class HTMLInline extends Text {}
	final class HTMLBlock extends Text {}

	final class Heading extends \CommonMark\Node {}
	final class Paragraph extends \CommonMark\Node {}
	final class Strong extends \CommonMark\Node {}
	final class Emphasis extends \CommonMark\Node {}
	final class ThematicBreak extends \CommonMark\Node {}
	final class SoftBreak extends \CommonMark\Node {}
	final class LineBreak extends \CommonMark\Node {}

	final class CustomBlock extends \CommonMark\Node {}
	final class FirstBlock extends \CommonMark\Node {}
	final class LastBlock extends \CommonMark\Node {}

	final class CustomInline extends \CommonMark\Node {}
	final class FirstInline extends \CommonMark\Node {}
	final class LastInline extends \CommonMark\Node {}

	final class Image implements \CommonMark\Interfaces\IMedia {
		public function setURL(string $url) : Image;
		public function getURL() : ?string;
		public function setTitle(string $title) : Image;
		public function getTitle() : ?string;
	}

	final class Link implements \CommonMark\Interfaces\IMedia {
		public function setURL(string $url) : Link;
		public function getURL() : ?string;
		public function setTitle(string $title) : Link;
		public function getTitle() : ?string;
	}
}

namespace CommonMark\Interfaces {
	
	final interface IList {
		public function setTight();
		public function isTight();

		public function setDelimitPeriod();
		public function hasPeriodDelim() : bool;
		public function setDelimitParen();
		public function hasParenDelim() : bool;
	}

	final interface IMedia {
		public function setURL(string $url) : \CommonMark\Interfaces\IMedia;
		public function getURL() : ?string;
		public function setTitle(string $title) : \CommonMark\Interfaces\IMedia;
		public function getTitle() : ?string;
	}

	final interface IVisitor {
		const Done;
		const Enter;
		const Leave;

		public function enter(\CommonMark\Node $node) : ?int;
		public function leave(\CommonMark\Node $node) : ?int;
	}

	final interface IVisitable {
		public function accept(CommonMark\Interfaces\IVisitor $visitor);
	}
}

namespace CommonMark {
	final abstract class Node implements \CommonMark\Interfaces\IVisitable {
		public function getNext() : ?Node;
		public function getPrevious() : ?Node;
		public function getParent() : ?Node;
		public function getFirstChild() : ?Node;
		public function getLastChild() : ?Node;
		public function appendChild(Node $child) : Node;
		public function prependChild(Node $child) : Node;
		public function insertBefore(Node $sibling) : Node;
		public function insertAfter(Node $sibling) : Node;
		public function replace(Node $node) : Node;

		public function accept(CommonMark\Interfaces\IVisitor $visitor);
	}

	final class Parser {
		public function __construct(int $options = 0);
		public function parse(string $content);
		public function finish() : Node;
	}

	function Parse(string $content, int $options = 0) : Node;

	function Render(Node $node) : string;
	function Render\HTML(Node $node) : string;
	function Render\XML(Node $node) : string;
	function Render\Latex(Node $node) : string;
	function Render\Man(Node $node) : string;
}

```
