--TEST--
CommonMark\Render HTML
--FILE--
<?php
$document = new CommonMark\Node\Document;
$document->appendChild(
	(new CommonMark\Node\Paragraph)
		->appendChild(
			(new CommonMark\Node\Text)
				->setLiteral("Hello World")));
echo CommonMark\Render\HTML($document);
?>
--EXPECT--
<p>Hello World</p>

