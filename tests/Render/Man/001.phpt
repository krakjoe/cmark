--TEST--
CommonMark\Render Man
--FILE--
<?php
$document = new CommonMark\Node\Document;
$document->appendChild(
	(new CommonMark\Node\Paragraph)
		->appendChild(
			(new CommonMark\Node\Text)
				->setLiteral("Hello World")));
echo CommonMark\Render\Man($document);
?>
--EXPECT--
.PP
Hello World


