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

	abstract final class List extends \CommonMark\Node {}
	final class BulletList extends List {}
	final class OrderedList extends List {}
	final class Item extends CommonMark\Node {}

	final class Text extends \CommonMark\Node {
		public function __construct(string $literal);

		public function setLiteral(string $ltieral) : Text;
		public function getLiteral() : ?string;
	}

	final class Code extends Text {}
	final class Strong extends Text {}
	final class Emphasis extends Text {}
	final class CodeBlock extends Text {}
	final class HTMLInline extends Text {}
	final class HTMLBlock extends Text {}

	final class Heading extends \CommonMark\Node {}
	final class Paragraph extends \CommonMark\Node {}
	final class ThematicBreak extends \CommonMark\Node {}
	final class SoftBreak extends \CommonMark\Node {}
	final class LineBreak extends \CommonMark\Node {}

	final class CustomBlock extends \CommonMark\Node {}
	final class FirstBlock extends \CommonMark\Node {}
	final class LastBlock extends \CommonMark\Node {}

	final class CustomInline extends \CommonMark\Node {}
	final class FirstInline extends \CommonMark\Node {}
	final class LastInline extends \CommonMark\Node {}

	abstract final class Media extends \CommonMark\Node {
		public function setURL(string $url) : Media;
		public function getURL() : ?string;
		public function setTitle(string $title) : Media;
		public function getTitle() : ?string;
	}

	final class Image extends Media;
	final class Link extends Media;
}

namespace CommonMark {
	final abstract class Node implements Visitable {
		public function getNext() : Node;
		public function getPrevious() : Node;
		public function getParent() : Node;
		public function getFirstChild() : Node;
		public function getLastChild() : Node;
		public function appendChild(Node $child) : Node;
		public function prependChild(Node $child) : Node;
		public function insertBefore(Node $sibling) : Node;
		public function insertAfter(Node $sibling) : Node;
		public function replace(Node $node) : Node;

		public function accept(CommonMark\Node\Visitor $visitor);
	}

	final class Parser {
		public function parse(string $content);
	}

	function Render(Node $node) : string;
	function Render\HTML(Node $node) : string;
	function Render\XML(Node $node) : string;
	function Render\Latex(Node $node) : string;
	function Render\Man(Node $node) : string;
}

```
