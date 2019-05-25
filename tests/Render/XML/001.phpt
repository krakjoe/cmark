--TEST--
CommonMark\Render XML
--FILE--
<?php
$text = new CommonMark\Node\Text;
$text->literal = "Hello World";

$document = new CommonMark\Node\Document;
$document->appendChild(
	(new CommonMark\Node\Paragraph)
		->appendChild($text));
if (CommonMark\Render\XML($document)) {
    echo "OK";
}
?>
--EXPECT--
OK

