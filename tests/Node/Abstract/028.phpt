--TEST--
CommonMark\Node clone
--FILE--
<?php
$parser = new CommonMark\Parser;
$parser->parse("
Hello World
===========

Paragraph:
  * item
  * item

**strong**
*emphasis*

some inline <html>html</html> is here

```somecode
<?php
some_code();
?>
```

[alt](url \"title\")
![alt](url \"title\")
");

$doc = $parser->finish();

$one = CommonMark\Render($doc);

$clone = clone $doc;

$two = CommonMark\Render($clone);

if ($one == $two) {
	echo "OK";
}
?>
--EXPECT--
OK
