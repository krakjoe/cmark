--TEST--
CommonMark\Render CommonMark
--FILE--
<?php
$document = new CommonMark\Node\Document;
$document->appendChild(
	(new CommonMark\Node\Paragraph)
		->appendChild(
			(new CommonMark\Node\Text)
				->setLiteral("Hello World")));
echo CommonMark\Render($document);
?>
--EXPECT--
Hello World



