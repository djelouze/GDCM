<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html" indent="yes"/>
<!-- XSL to convert XML GDCM2 data dictionay into HTML form -->
  <xsl:template match="/">
    <html>
      <body>
        <table border="1">
          <tr bgcolor="#d6d6d6"> <!--rgb(214,214,214) -->
            <th>Group</th>
            <th>Element</th>
            <th>VR</th>
            <th>VM</th>
            <th>Description</th>
            <th>Retired</th>
          </tr>
<!-- The main template that loop over all dict/entry -->
          <xsl:for-each select="dict/entry">
            <tr>
              <td>
                <xsl:value-of select="@group"/>
              </td>
              <td>
                <xsl:value-of select="@element"/>
              </td>
              <td>
                <xsl:for-each select="representations/representation">
                  <xsl:value-of select="@vr"/>
                  <xsl:if test="position() != last()">
                    <br/>
                  </xsl:if>
                </xsl:for-each>
              </td>
              <td>
                <xsl:for-each select="representations/representation">
                  <xsl:value-of select="@vm"/>
                  <xsl:if test="position() != last()">
                    <br/>
                  </xsl:if>
                </xsl:for-each>
              </td>
              <td>
                <xsl:value-of select="description"/>
              </td>
              <td>
                <xsl:if test="@retired != &quot;false&quot;">
                  <xsl:text> (RET)</xsl:text>
                </xsl:if>
              </td>
            </tr>
          </xsl:for-each>
        </table>
      </body>
    </html>
  </xsl:template>
</xsl:stylesheet>
