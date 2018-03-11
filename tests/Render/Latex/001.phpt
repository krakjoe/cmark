--TEST--
CommonMark\Render Latex
--FILE--
<?php
$document = new CommonMark\Node\Document;
$document->appendChild(
	(new CommonMark\Node\Paragraph)
		->appendChild(
			(new CommonMark\Node\Text)
				->setLiteral("Hello World")));
echo CommonMark\Render\Latex($document);
?>
--EXPECT--
Hello World



