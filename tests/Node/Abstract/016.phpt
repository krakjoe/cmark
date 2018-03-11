--TEST--
CommonMark\Node Insert After
--FILE--
<?php
$document = new CommonMark\Node\Document;

$para = new CommonMark\Node\Paragraph;

$document->appendChild($para);

$text[0] = new CommonMark\Node\Text;
$text[1] = new CommonMark\Node\Text;

$para->appendChild($text[1]);

$text[1]->insertAfter($text[0]);

echo "OK";
?>
--EXPECT--
OK
