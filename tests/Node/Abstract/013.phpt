--TEST--
CommonMark\Node Insert Before
--FILE--
<?php
$document = new CommonMark\Node\Document;

$para = new CommonMark\Node\Paragraph;

$document->appendChild($para);

$text[0] = new CommonMark\Node\Text;
$text[1] = new CommonMark\Node\Text;

$para->appendChild($text[0]);

$text[0]->insertBefore($text[1]);

echo "OK";
?>
--EXPECT--
OK
