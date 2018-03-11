--TEST--
CommonMark\Render XML
--FILE--
<?php
$document = new CommonMark\Node\Document;
$document->appendChild(
	(new CommonMark\Node\Paragraph)
		->appendChild(
			(new CommonMark\Node\Text)
				->setLiteral("Hello World")));
echo CommonMark\Render\XML($document);
?>
--EXPECT--
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE document SYSTEM "CommonMark.dtd">
<document xmlns="http://commonmark.org/xml/1.0">
  <paragraph>
    <text>Hello World</text>
  </paragraph>
</document>

