--TEST--
CommonMark\Render CommonMark
--FILE--
<?php
$text = new CommonMark\Node\Text;
$text->literal = "Hello World";

$document = new CommonMark\Node\Document;
$document->appendChild(
	(new CommonMark\Node\Paragraph)
		->appendChild($text));
echo CommonMark\Render($document);
?>
--EXPECT--
Hello World



